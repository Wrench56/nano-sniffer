#include <Arduino.h>

#include "comhub.h"
#include "selector.h"

#include "transport.h"
#include "ble_transport.h"
#include "uart_transport.h"

#include "utility.h"

ITransport* gio = nullptr;
UartTransport usb_serial(Serial);
BLETransport ble_serial;

void setup() {
    init_uart();
    init_ble();
    transport_type_t type = pick_transport_type(0);
    if (type == TRANSPORT_USB) {
        gio = &usb_serial;
        GIO_WRITE(gio, "Using USB Serial as control transport!");
    } else if (type == TRANSPORT_BLE) {
        gio = &ble_serial;
        while (!txChar.subscribed() || !gBleCentral.connected()) {
            delay(1);
            BLE.poll();
        }
        GIO_WRITE(gio, "Using BLE Serial as control transport!");
    } else {
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, HIGH);
        return;
    }

    init_comhub(gio);
}

void loop() {
    handle_comhub(gio);
}
