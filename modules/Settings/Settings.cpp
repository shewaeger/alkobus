//

#include "Settings.h"
#include <Arduino.h>
#include <EEPROM.h>

Settings::Settings() {
    for(int i = 0; i < sizeof(settings); i++){
        *(((uint8_t *)&settings) + i) = EEPROM.read(i);
    }
}

//
// Created by shewa on 02.02.20.
void Settings::saveSettings() {
    for(int i = 0; i < sizeof(settings); i++){
        EEPROM.update(i, *(((uint8_t *)&settings) + i));
    }
}

Settings_struct * Settings::getStruct() {
    return &settings;
}



