//
// Created by shewa on 12.02.2020.
//

#include "TenSwitch.h"
#include <Arduino.h>
void TenSwitch::setup() {
    pinMode(37, OUTPUT);
}

void TenSwitch::enable() {
    digitalWrite(37, 1);
}

void TenSwitch::disable() {
    digitalWrite(37, 0);
}
