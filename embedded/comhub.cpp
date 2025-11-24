#include <Arduino.h>

#include "comhub.h"
#include "main.h"

#include "transport.h"
#include "uart.h"
#include "utility.h"

static char input_buf[NS_COMHUB_BUF_SIZE];
static comhub_state_t currstate = COMHUB_MENU;
static int available = 0;
static constexpr char strheader[] = "[ ======================== ]\n\r";
static constexpr char strempty[] = "[ >                        ]\n\r";

void init_comhub(ITransport* gio) {
    GIO_WRITE(gio, "\n\r");
    GIO_WRITE(gio, strheader);
    GIO_WRITE(gio, "[ > Init Nano-Sniffer      ]\n\r");
    GIO_WRITE(gio, "[ >              v" NS_VERSION_STR " ]\n\r");
    GIO_WRITE(gio, strempty);
    GIO_WRITE(gio, "[ > Built on:              ]\n\r");
    GIO_WRITE(gio, "[ >   "__DATE__ " " __TIME__" ]\n\r");
    GIO_WRITE(gio, strheader);
    GIO_WRITE(gio, "\n\r");
}

static void show_menu(ITransport* gio) {
    GIO_WRITE(gio, "\n\r");
    GIO_WRITE(gio, "[ =[ Menu ]=============== ]\n\r");
    GIO_WRITE(gio, strempty);
    GIO_WRITE(gio, "[ > [h]elp - show this     ]\n\r");
    GIO_WRITE(gio, "[ >                        ]\n\r");
    GIO_WRITE(gio, strheader);
    GIO_WRITE(gio, "\n\r");
}

void handle_comhub(ITransport* gio) {
    available = gio->available();
    if (available > 0) {
        switch (currstate) {
            case COMHUB_MENU:
                handle_menu(gio);
                break;
            default:
                handle_menu(gio);
                break;
        }

        gio->drain();
    }
}

static inline void handle_menu(ITransport* gio) {
    if (available == 1) {
        char c = gio->read();
        if (c == 'h') {
            show_menu(gio);
        } else if (c == 'r') {
            uart_relay(gio);
        }
    } else if (available == 4) {
        char buf[4] = { 0 };
        read_to_buffer(buf, available, gio);
        if (strncmp(buf, "help", 4) == 0) {
            show_menu(gio);
        } else if (strncmp(buf, "relay", 5) == 0) {
            uart_relay(gio);
        }
    } else {
        GIO_WRITE(gio, "Invalid menu command!\n\r");
    }
}

static inline void read_to_buffer(char* buffer, uint16_t length, ITransport* gio) {
    for (uint16_t i = 0; i < length; ++i) {
        int ch = gio->read();
        if (ch < 0) break;
        buffer[i] = static_cast<char>(ch);
    }
}
