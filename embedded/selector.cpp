#include <Arduino.h>
#include <ArduinoBLE.h>

#include "ble_transport.h"

#include "selector.h"

transport_type_t pick_transport_type(uint64_t timeout_ms) {
    uint64_t start = millis();

    for (;;) {
        if (Serial && Serial.rts()) {
            return TRANSPORT_USB;
        }

        BLEDevice central = BLE.central();
        if (central && central.connected()) {
            gBleCentral = central;
            return TRANSPORT_BLE;
        }

        if (timeout_ms && (millis() - start) > timeout_ms) {
            return TRANSPORT_NONE;
        }

        BLE.poll();
        delay(10);
    }
}
