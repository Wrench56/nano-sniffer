#include "ble_transport.h"

BLEService bleService(BLE_SERVICE_UUID);

BLECharacteristic rxChar(
    BLE_CHAR_RX_UUID,
    BLEWrite | BLEWriteWithoutResponse,
    244
);

BLECharacteristic txChar(
    BLE_CHAR_TX_UUID,
    BLENotify,
    244
);

BLEDevice gBleCentral;

void init_ble(void) {
    if (!BLE.begin()) {
        return;
    }

    BLE.setLocalName(NS_BLUETOOTH_NAME);
    BLE.setAdvertisedService(bleService);

    bleService.addCharacteristic(rxChar);
    bleService.addCharacteristic(txChar);

    BLE.addService(bleService);
    BLE.advertise();
}

bool ble_has_central() {
    return (bool)gBleCentral;
}

bool ble_central_connected() {
    return (bool)gBleCentral && gBleCentral.connected();
}

void BLETransport::onBleDataReceived(const uint8_t* data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        rxBuffer += (char)data[i];
    }
}

int BLETransport::available() {
    return rxBuffer.length();
}

int BLETransport::read() {
    if (rxBuffer.isEmpty()) {
        return -1;
    }
    char c = rxBuffer[0];
    rxBuffer.remove(0, 1);
    return (uint8_t)c;
}

uint32_t BLETransport::write(const uint8_t* d, size_t len) {
    if (gBleCentral.connected()) {
        txChar.writeValue(d, len);
        return len;
    }
}

void BLETransport::drain() {
    rxBuffer.remove(0, rxBuffer.length());
}
