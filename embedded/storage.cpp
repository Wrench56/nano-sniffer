#include "storage.h"

#include <Arduino.h>
#include <fds.h>

static bool op_finished;
const static __attribute__((aligned(4))) uint8_t storage_data_buff[1024] = { 0 };
storage_t storage = { 0 };

static void fds_evt_handler(fds_evt_t const * p_fds_evt) {
    op_finished = true;
    switch (p_fds_evt->id) {
       case FDS_EVT_INIT:
            if (p_fds_evt->result != NRF_SUCCESS) {
                /* Init failed */
            }
            break;
        default:
            break;
    }
}

storage_error_t storage_init(void) {
    op_finished = false;
    ret_code_t ret = fds_register(fds_evt_handler);
    if (ret != NRF_SUCCESS) {
        return STORAGE_REG_ERR;
    }

    op_finished = false;
    ret = fds_init();
    if (ret != NRF_SUCCESS) {
        return STORAGE_INIT_ERR;
    }

    return STORAGE_OK;
}

void storage_load(void) {
    op_finished = false;
    ret_code_t ret = FDS_ERR_NOT_FOUND;
    fds_record_desc_t record_desc = { 0 };
    fds_flash_record_t flash_record = { 0 };
    fds_find_token_t ftok = { 0 };

    while (fds_record_find(STORAGE_FILE_ID, STORAGE_RECORD_KEY, &record_desc, &ftok) == FDS_SUCCESS) {
        ret = fds_record_open(&record_desc, &flash_record);
        memcpy(&storage, flash_record.p_data, sizeof(storage_t));
        ret = fds_record_close(&record_desc);
    }

    if (ret == FDS_ERR_NOT_FOUND || storage.magic != 0xDEADBEEF) {
        /* Load and save defaults */
        storage.magic = 0xDEADBEEF;
        strcpy(storage.name, const_cast<char*>("John Doe"));
        storage_save();
    }
}

void storage_save(void) {
    op_finished = false;
    ret_code_t ret = FDS_SUCCESS;
    fds_record_t record = { 0 };
    fds_record_desc_t record_desc = { 0 };
    fds_find_token_t ftok = { 0 };

    memcpy(const_cast<uint8_t*>(storage_data_buff), &storage, sizeof(storage_t));
    record.file_id = STORAGE_FILE_ID;
    record.key = STORAGE_RECORD_KEY;
    record.data.p_data = storage_data_buff;
    record.data.length_words = (sizeof(storage_t) + 3) / 4;

    if (fds_record_find(STORAGE_FILE_ID, STORAGE_RECORD_KEY, &record_desc, &ftok) == FDS_SUCCESS) {
        ret = fds_record_update(&record_desc, &record);
  } else {
        ret = fds_record_write(&record_desc, &record);
  }

  if (ret == FDS_SUCCESS) {
    while (!op_finished) {}
  }
}
