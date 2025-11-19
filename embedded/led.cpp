#include <Arduino.h>

#include "led.h"

static bool curr_state = false;

void led_init(void) {
    pinMode(LED_BUILTIN, OUTPUT);
}

void led_set(led_state_t led_state) {
    digitalWrite(LED_BUILTIN, led_state ? HIGH : LOW);
}

void led_toggle(void) {
    digitalWrite(LED_BUILTIN, curr_state ? HIGH : LOW);
}
