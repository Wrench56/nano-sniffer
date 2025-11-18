#ifndef NS_BLE_TRANSPORT_H
#define NS_BLE_TRANSPORT_H

#include <ArduinoBLE.h>
#include "transport.h"

#define NS_BLUETOOTH_NAME "NanoSniffer"

#define BLE_SERVICE_UUID   "19B10000-E8F2-537E-4F6C-D104768A1214"
#define BLE_CHAR_RX_UUID   "19B10001-E8F2-537E-4F6C-D104768A1214"
#define BLE_CHAR_TX_UUID   "19B10002-E8F2-537E-4F6C-D104768A1214"

extern BLEService        bleService;
extern BLECharacteristic rxChar;
extern BLECharacteristic txChar;

extern BLEDevice         gBleCentral;

class BLETransport : public ITransport {
public:
    String rxBuffer;

    BLETransport() = default;

    void onBleDataReceived(const uint8_t* data, size_t len);
    int available() override;
    int read() override;
    uint32_t write(const uint8_t* d, size_t len) override;
    void drain() override;
};

void init_ble(void);
bool ble_has_central();
bool ble_central_connected();

#endif // NS_BLE_TRANSPORT_H
