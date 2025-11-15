#ifndef NS_COMHUB_H
#define NS_COMHUB_H

#include <stdint.h>

#define COMHUB_BAUD_RATE 115200
#define NS_COMHUB_BUF_SIZE 256

typedef enum {
    COMHUB_MENU,
} comhub_state_t;

void init_comhub(void);
void handle_comhub(void);

static inline void read2Buffer(char* buffer, size_t length);
static inline void handle_menu();

#endif // NS_COMHUB_H
