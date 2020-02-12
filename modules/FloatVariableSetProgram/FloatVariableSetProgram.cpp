//
// Created by shewa on 10.02.2020.
//

#include <LiquidCrystal_I2C.h>
#include <ModManager.h>
#include "FloatVariableSetProgram.h"
#include <LcdOverflowString.h>
#include <EventBus.h>
#include <Keyboard.h>

void FloatVariableSetProgram::setup() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    lcd->clear();
    lcdOverflowString = new LcdOverflowString(name, lcd, 800, 0);
    if(*variable > maxValue){
        *variable = maxValue;
    }
    if(*variable < minValue){
        *variable = minValue;
    }
    lcd->setCursor(0, 1);
    lcd->print(*variable);
    this->isExit = false;
}

void FloatVariableSetProgram::loop() {
    if(isExit){
        delete lcdOverflowString;
        exit();
    }
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    lcdOverflowString->loop();
    lcd->setCursor(0,1);
    lcd->print(*variable);
}

void FloatVariableSetProgram::event(Event *event) {
    switch (event->type){
        case SHORT_PUSH_KEY_EVENT:
        case LONG_PUSH_KEY_EVENT:
            switch (*(uint8_t*)event->data){
                case BUTTON_DOWN:
                    variableDown();
                    break;
                case BUTTON_UP:
                    variableUp();
                    break;
                case BUTTON_OK:
                    this->isExit = true;
            }
    }
}

char *FloatVariableSetProgram::getName() {
    return name;
}

FloatVariableSetProgram::FloatVariableSetProgram(char *name, float *variable, float minValue, float maxValue,
                                                 float step) {
    this->name = name;
    this->name = name;
    this->variable = variable;
    this->minValue = minValue;
    this->maxValue = maxValue;
    this->step = step;
}

void FloatVariableSetProgram::variableUp() {
    *variable += step;
    if(*variable > maxValue){
        *variable = maxValue;
    }
}

void FloatVariableSetProgram::variableDown() {
    *variable -= step;
    if(*variable < minValue){
        *variable = minValue;
    }
}

