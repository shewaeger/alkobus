//
// Created by shewa on 10.02.2020.
//

#include <Keyboard.h>
#include <EventBus.h>
#include <ModManager.h>
#include "TimeSetProgram.h"
#include <LiquidCrystal_I2C.h>
#define CURSOR_CHAR ((char)0x6e)
char positions[4] = {0, 3, 6, 9};

char * ultostr(unsigned long num, char * buf, char length){
    char tmp[5];
    char i = 0;
    while(num){
        tmp[i] = '0' + num % 10;
        num /= 10;
        i++;
    }
    tmp[i] = 0;
    size_t strsize = strlen(tmp);
    if(strsize < length){
        for(i = 0; i < length - strsize; i++){
            *buf = '0';
            buf++;
        }
    }
    for(i = strsize - 1; i >= 0; i--){
        *buf = tmp[i];
        *buf++;
    }
    *buf = 0;
    return buf;
}

void TimeSetProgram::loop() {
    char buffer[17] = "";
    memset(buffer, '0', 12);
    memset(buffer + 12, ' ', 4);
    buffer[16] = 0;
    char *bufPtr = buffer;
    if(isExit){
        exit(0);
    }
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
//    lcdOverflowString->loop();
    lcd->setCursor(0,0);
    unsigned long hour = (*variable) / 3600000;
    unsigned long mod = (*variable) % 3600000;
    unsigned long minutes = mod / 60000;
    mod %= 60000;
    unsigned long seconds = mod / 1000;
    unsigned long mills = mod % 1000;
    if(format & FORMAT_HOUR_MASK) {
        bufPtr = ultostr(hour, bufPtr, 2);
    }
    if(format & FORMAT_MINUTES_MASK){
        *bufPtr = ':';
        *bufPtr++;
        bufPtr = ultostr(minutes, bufPtr, 2);
    }
    if(format & FORMAT_SECONDS_MASK){
        *bufPtr = ':';
        *bufPtr++;
        bufPtr = ultostr(seconds, bufPtr, 2);
    }
    if(format & FORMAT_MILLIS_MASK){
        *bufPtr = ':';
        *bufPtr++;
        ultostr(mills, bufPtr, 3);
    }
    lcd->setCursor(0,0);
    lcd->print(buffer);
    for(int i = 0; i < 4; i ++) {
        lcd->setCursor(positions[i], 1);
        if(i == selector)
            lcd->print((char) 0);
        else
            lcd->print(' ');
    }
}

TimeSetProgram::TimeSetProgram(char *name, unsigned long *variable, unsigned long maxValue, unsigned char format) {
    this->name = name;
    this->variable = variable;
    this->format = format;
    this->selector = 0;
    this->maxTime = maxValue;
    this->isExit = false;
}

void TimeSetProgram::setup() {
    ModManager::getManager()->getLCD()->clear();
    this->name = name;
    this->variable = variable;
    this->format = format;
    this->selector = 0;
    this->isExit = false;
}

void TimeSetProgram::event(Event *event) {
    switch (event->type){
        case SHORT_PUSH_KEY_EVENT:
        case LONG_PUSH_KEY_EVENT:
            switch (*(uint8_t *)event->data){
                case BUTTON_LEFT:
                    selectorLeft();
                    break;
                case BUTTON_RIGHT:
                    selectorRight();
                    break;
                case BUTTON_UP:
                    buttonUp();
                    break;
                case BUTTON_DOWN:
                    buttonDown();
                    break;
                case BUTTON_OK:
                    isExit = true;
                    break;
            }
    }
}

char *TimeSetProgram::getName() {
    return this->name;
}

void TimeSetProgram::selectorLeft() {
    if(selector != 0)
        selector --;
}

void TimeSetProgram::selectorRight() {
    switch (selector){
        case 0:
            if(format & FORMAT_MINUTES_MASK)
                selector++;
            break;
        case 1:
            if(format & FORMAT_SECONDS_MASK)
                selector++;
            break;
        case 2:
            if(format & FORMAT_MILLIS_MASK)
                selector++;
            break;
    }
}

void TimeSetProgram::buttonDown() {
    unsigned long tmp;
    switch (selector){
        case 0:
            if(*variable >= 3600000)
                (*variable) -= 3600000;
            break;
        case 1: // minutes
            tmp =  ((*variable) % 3600000) / 60000;
            if(tmp != 0)
                (*variable) -= 60000;
            break;
        case 2: //seconds
            tmp = (((*variable) % 3600000) % 60000) / 1000;
            if(tmp != 0)
                (*variable) -= 1000;
            break;
        case 3:
            tmp = (((*variable) % 3600000) % 60000) % 1000;
            if(tmp != 0)
                (*variable)--;
    }
}

void TimeSetProgram::buttonUp() {
    unsigned long tmp;
    switch (selector){
        case 0:
            if((*variable) + 3600000 > maxTime)
                return;
            tmp = (*variable) / 3600000;
            if(tmp < 99)
                *variable += 3600000;
            break;
        case 1: // minutes
            if((*variable) + 60000 > maxTime)
                return;
            tmp =  ((*variable) % 3600000) / 60000;
            if(tmp < 59)
                *variable += 60000;
            break;
        case 2: //seconds
            if((*variable) + 1000 > maxTime)
                return;
            tmp = (((*variable) % 3600000) % 60000) / 1000;
            if(tmp < 59)
                *variable += 1000;
            break;
        case 3: //millis
            if((*variable) + 1 > maxTime)
                return;
            tmp = (((*variable) % 3600000) % 60000) % 1000;
            if(tmp < 999)
                (*variable)++;
    }
}

void TimeSetProgram::setMaxTime(unsigned long maxTime) {
    this->maxTime = maxTime;
}
