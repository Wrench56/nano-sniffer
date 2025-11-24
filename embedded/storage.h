#ifndef NS_STORAGE_H
#define NS_STORAGE_H

#include <stdint.h>

#define STORAGE_FILE_ID 0x1111
#define STORAGE_RECORD_KEY 0x2222

typedef enum {
    STORAGE_OK = 0,
    STORAGE_REG_ERR,
    STORAGE_INIT_ERR,
} storage_error_t;

typedef struct {
    uint32_t magic;
    char name[32];
} storage_t;

extern storage_t storage;

storage_error_t storage_init(void);
void storage_load(void);
void storage_save(void);

#endif // NS_STORAGE_H
