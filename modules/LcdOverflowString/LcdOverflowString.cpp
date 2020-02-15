//
// Created by shewa on 08.02.2020.
//

#include "LcdOverflowString.h"
#include <LiquidCrystal_I2C.h>

LcdOverflowString::LcdOverflowString(char *string, LiquidCrystal_I2C *lcd, uint32_t offsetTime, uint8_t position) {
    this->string = string;
    this->lcd = lcd;
    this->offsetTime = offsetTime;
    this->position = position;
    this->firstLastOffsetTime = offsetTime * 2;
    this->currentOffset = 0;
    this->strlength = strlen(string);
    this->lastOffsetTime = millis();
    lcd->setCursor(0, position);
    if(strlength <= 16){
        lcd->print(this->string);
        uint32_t counter = 16 - strlength;
        while(counter--){
            lcd->print(' ');
        }
        return;
    }

    char end = string[16];
    this->string[16] = 0;
    lcd->print(this->string);
    this->string[16] = end;
}

void LcdOverflowString::loop() {
    if(strlength < 16)
        return;
    uint32_t currentOffsetTime = currentOffset == 0 || strlength - 15 == currentOffset ? firstLastOffsetTime : offsetTime;
    if(millis() - lastOffsetTime < currentOffsetTime)
        return;

    currentOffset++;
    if(currentOffset >= strlength - 15)
        currentOffset = 0;

    char end = this->string[currentOffset + 16];
    this->string[currentOffset + 16] = 0;
    lcd->setCursor(0, position);
    lcd->print(this->string + currentOffset);
    this->string[currentOffset + 16] = end;
    this->lastOffsetTime = millis();
}