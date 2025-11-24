#include <stdint.h>

#include <Arduino.h>

#include "uart.h""
#include "storage.h"
#include "utility.h"

void uart_relay(ITransport* gio) {
    GIO_WRITE(gio, "[ RDY ] Relaying UART messages...");
    uint32_t baudrate = storage.uart_baudrate;
    if (verify_baudrate(baudrate)) {
        Serial1.begin(baudrate);
    } else {
        GIO_WRITE(gio, "Warning: Invalid standard baudrate!\n");
    }

    uint8_t data[256];
    uint32_t avail = 0;
    uint8_t state = 0;
    while (true) {
        avail = Serial1.available();
        if (avail != 0) {
            data[0] = avail > 255 ? 255 : avail;
            Serial1.readBytes(&data[1], data[0]);
            gio->write(data, data[0] + 1);
        }

        avail = gio->available();
        if (avail != 0) {
            for (uint32_t i = 0; i < avail; i++) {
                uint8_t chr = gio->read();
                if (chr == 'n') {
                    state = 1;
                } else if (chr == 's' && state == 1) {
                    ++state;
                } else if (chr == 'q' && state == 2) {
                    Serial1.end();
                    return;
                } else {
                    state = 0;
                }
            }
        }
    }
}

static bool verify_baudrate(uint32_t baudrate) {
    switch (baudrate) {
        case 110:
        case 300:
        case 600:
        case 1200:
        case 2400:
        case 4800:
        case 9600:
        case 14400:
        case 19200:
        case 38400:
        case 57600:
        case 115200:
        case 230400:
        case 460800:
        case 921600:
        case 1000000:
        case 2000000:
            return true;
        default:
            return false;
    }
}
