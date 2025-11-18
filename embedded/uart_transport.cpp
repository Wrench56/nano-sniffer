#include "uart_transport.h"

void init_uart(void) {
    Serial.begin(NS_SERIAL_BAUD_RATE);
}

int UartTransport::available() {
    return io.available();
}

int UartTransport::read() {
    return io.read();
}

uint32_t UartTransport::write(const uint8_t* d, size_t l) {
    return io.write(++d, l - 1);
}

void UartTransport::flush() {
    io.flush();
}

void UartTransport::drain() {
    int avail = io.available();
    while (avail-- > 0) {
        io.read();
    }
}
