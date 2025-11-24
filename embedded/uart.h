#ifndef NS_UART_H
#define NS_UART_H

#include <stdint.h>

#include "transport.h"

static bool verify_baudrate(uint32_t);
void uart_relay(ITransport* gio);

#endif // NS_UART_H
