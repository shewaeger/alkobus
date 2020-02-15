//
// Created by shewa on 15.02.2020.
//

#include <ModManager.h>
#include <Arduino.h>
#include <temperature.h>
#include <Settings.h>
#include <LiquidCrystal_I2C.h>
#include <EventBus.h>
#include <Keyboard.h>
#include "FindThermometerProgram.h"

void FindThermometerProgram::setup() {
    this->isOk = false;
    this->isOk2 = false;
    this->isExit = false;
    this->found = false;
}

void FindThermometerProgram::loop() {
    if (isExit) {
        exit(0);
        return;
    }

    if (isOk) {
        Settings_struct *settings = ModManager::getManager()->getSettings()->getStruct();
        found = ModManager::getManager()->getThermometers()->findThermometer(addr);
    }

}

void FindThermometerProgram::event(Event *event) {
    if(event->type == SHORT_PUSH_KEY_EVENT && (*(uint8_t *) event->data) == BUTTON_OK){
        if(!isOk)
            isOk = true;
        else
            isExit = true
    }
}

char *FindThermometerProgram::getName() {
    return name;
}

FindThermometerProgram::FindThermometerProgram(char *name, uint8_t *addr) : name(name), addr(addr) {}

void FindThermometerProgram::drawScreen() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    if(!isOk){
        lcd->setCursor(0,0);
        lcd->print("Insert sensor...    ");
        lcd->setCursor(0, 1);
        lcd->print((char)0x7e);
        lcd->print(" Ok                ");
    }
    else{
        if(found){
            lcd->setCursor(0, 0);
            lcd->print("Sensor found    ");
            lcd->setCursor(0, 1);
            lcd->print((char)0x7e);
            lcd->print(" Exit           ");
        }
        else{
            lcd->setCursor(0, 0);
            lcd->print("Sensor not found");
            lcd->setCursor(0, 1);
            lcd->print((char)0x7e);
            lcd->print(" Exit           ");
        }
    }
}
