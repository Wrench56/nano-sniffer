#include <Arduino.h>
#include "comhub.h"

void setup() {
    init_comhub();
}

void loop() {
    handle_comhub();
}
