#ifndef NS_COMHUB_H
#define NS_COMHUB_H

#include <stdint.h>

#include "transport.h"

#define NS_COMHUB_BUF_SIZE 256

typedef enum {
    COMHUB_MENU,
} comhub_state_t;

void init_comhub(ITransport* gio);
void handle_comhub(ITransport* gio);

static inline void read_to_buffer(char* buffer, uint16_t length, ITransport* gio);
static inline void handle_menu(ITransport* gio);

#endif // NS_COMHUB_H
