#ifndef NS_SELECTOR_H
#define NS_SELECTOR_H

#include <ArduinoBLE.h>
#include <stdint.h>

typedef enum {
    TRANSPORT_NONE,
    TRANSPORT_USB,
    TRANSPORT_BLE,
} transport_type_t;

transport_type_t pick_transport_type(uint64_t timeout_ms);

#endif // NS_SELECTOR_H
