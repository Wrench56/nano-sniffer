#ifndef NS_SERIAL_TRANSPORT_H
#define NS_SERIAL_TRANSPORT_H

#include <Arduino.h>

#include "transport.h"

#define NS_SERIAL_BAUD_RATE 115200

class UartTransport : public ITransport {
public:
    Stream& io;

    explicit UartTransport(Stream& s) : io(s) {}

    int available() override;
    int read() override;
    uint32_t write(const uint8_t* d, size_t l) override;
    void flush() override;
    void drain() override;
};

void init_uart(void);

#endif // NS_SERIAL_TRANSPORT_H
