//
// Created by shewa on 12.02.2020.
//

#include "Speaker.h"
#include <Arduino.h>
void Speaker::disable() {
    analogWrite(9, 0);
}

void Speaker::enable() {
    analogWrite(9, 150);
}

void Speaker::setup() {
    pinMode(9, OUTPUT);
}
