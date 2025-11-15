#include <Arduino.h>
#include "comhub.h"
#include "main.h"

static char input_buf[NS_COMHUB_BUF_SIZE];
static comhub_state_t currstate = COMHUB_MENU;
static int available = 0;
static const arduino::__FlashStringHelper* strheader = F("[ ======================== ]");
static const arduino::__FlashStringHelper* strempty = F("[ >                        ]");

void init_comhub(void) {
    Serial.begin(COMHUB_BAUD_RATE, SERIAL_8N1);
    while (!Serial) {}

    Serial.println(F(" "));
    Serial.println(strheader);
    Serial.println(F("[ > Init Nano-Sniffer      ]"));
    Serial.println(F("[ >              v" NS_VERSION_STR " ]"));
    Serial.println(strempty);
    Serial.println(F("[ > Built on:              ]"));
    Serial.println(F("[ >   "__DATE__ " " __TIME__" ]"));
    Serial.println(strheader);
    Serial.println();
}

static void show_menu(void) {
    Serial.println(F("[ =[ Menu ]=============== ]"));
    Serial.println(strempty);
    Serial.println(F("[ > [h]elp - show this     ]"));
    Serial.println(F("[ >                        ]"));
    Serial.println(strheader);
}

void handle_comhub(void) {
    available = Serial.available();
    if (available > 0) {
        switch (currstate) {
            case COMHUB_MENU:
                handle_menu();
                break;
            default:
                handle_menu();
                break;
        }

        /* Drain Serial buffer manually */
        while (available--) {
            Serial.read();
        }
    }
}

static inline void handle_menu() {
    if (available == 1) {
        char c = Serial.read();
        if (c == 'h') {
            show_menu();
        }
    } else if (available == 4) {
        char buf[4] = { 0 };
        read2Buffer(buf, available);
        if (strncmp(buf, "help", 4) == 0) {
            show_menu();
        }
    } else {
        Serial.println("Invalid menu command!");
    }
}

static inline void read2Buffer(char* buffer, size_t length) {
    for (int i = 0; i < length; i++) {
        buffer[i] = Serial.read();
    }
}
