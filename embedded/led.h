#ifndef NS_LED_H
#define NS_LED_H

#include <stdbool.h>

typedef enum {
    LED_ON = true,
    LED_OFF = false,
} led_state_t;

void led_init(void);
void led_set(led_state_t led_state);
void led_toggle(void);

#endif // NS_LED_H
