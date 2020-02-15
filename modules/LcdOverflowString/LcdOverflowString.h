//
// Created by shewa on 08.02.2020.
//

#ifndef MEGA_POWER_DRIVER_LCDOVERFLOWSTRING_H
#define MEGA_POWER_DRIVER_LCDOVERFLOWSTRING_H

#include <Arduino.h>

class LiquidCrystal_I2C;

class LcdOverflowString {
private:
    char * string;
    LiquidCrystal_I2C *lcd;
    uint32_t offsetTime;
    uint8_t position;
    uint32_t lastOffsetTime;
    uint32_t firstLastOffsetTime;
    uint32_t currentOffset;
    size_t strlength;
public:
    LcdOverflowString(char * string, LiquidCrystal_I2C *lcd, uint32_t offsetTime, uint8_t position);

    void loop(void);
};


#endif //MEGA_POWER_DRIVER_LCDOVERFLOWSTRING_H
