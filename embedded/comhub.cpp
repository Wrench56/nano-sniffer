#include <Arduino.h>
#include "comhub.h"
#include "main.h"

void init_comhub(void) {
    Serial.begin(COMHUB_BAUD_RATE, SERIAL_8N1);
    while (!Serial) {}

    Serial.println(F(" "));
    Serial.println(F("[ ======================== ]"));
    Serial.println(F("[ > Init Nano-Sniffer      ]"));
    Serial.println(F("[ >              v" NS_VERSION_STR " ]"));
    Serial.println(F("[ >                        ]"));
    Serial.println(F("[ > Built on:              ]"));
    Serial.println(F("[ >   "__DATE__ " " __TIME__" ]"));
    Serial.println(F("[ ======================== ]"));
    Serial.println();
}
