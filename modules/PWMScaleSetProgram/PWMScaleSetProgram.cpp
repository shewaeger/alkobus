//
// Created by shewa on 11.02.2020.
//

#include <Arduino.h>
#include "PWMScaleSetProgram.h"
#include <LcdOverflowString.h>
#include <LiquidCrystal_I2C.h>
#include <ModManager.h>
#include <EventBus.h>
#include <Keyboard.h>

void PWMScaleSetProgram::setup() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    lcdOverflowString = new LcdOverflowString(getName(), lcd, 800, 0);
    isExit = false;
}

void PWMScaleSetProgram::loop() {
    if(isExit){
        delete lcdOverflowString;
        exit(0);
    }
    lcdOverflowString->loop();
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    lcd->setCursor(0, 1);
    if(*variable){
        lcd->print("count/hour      ");
    } else {
        lcd->print("count/minute    ");
    }
}

void PWMScaleSetProgram::event(Event *event) {
    if(event->type == SHORT_PUSH_KEY_EVENT){
        switch (*(uint8_t*)event->data){
            case BUTTON_DOWN:
                *variable = true;
                break;
            case BUTTON_UP:
                *variable = false;
                break;
            case BUTTON_OK:
                isExit = true;
                break;
        }
    }
}

char *PWMScaleSetProgram::getName() {
    return "PWM scale";
}

PWMScaleSetProgram::PWMScaleSetProgram(bool *variable) : variable(variable) {
    this->variable = variable;
    this->isExit = false;
}
