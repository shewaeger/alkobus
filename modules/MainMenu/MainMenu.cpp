//
// Created by shewa on 21.10.19.
//

#include "MainMenu.h"
#include <Arduino.h>
#include <ModManager.h>
#include <LiquidCrystal_I2C.h>
#include <Keyboard.h>
#include <VoltageProgram.h>
#include <list_utils.h>
#define CURSOR_CHAR ((char)0x7e)

MainMenu::MainMenu() : Program() {

}

MainMenu::~MainMenu() {

}

void MainMenu::backgroundLoop() {
    Program::backgroundLoop();
}

void MainMenu::setup() {
    this->selector = 0;
    this->selectorPos = 0;
    this->lastSelector = 0;
    this->redrawScreen = true;
    this->programSelected = false;
    this->bufferSwitch = false;
    Serial.println("initializing variables...");
    VoltageProgram *voltageProgram1 = new VoltageProgram("VoltageP1");
    Serial.println("Create voltage program 1");
    Serial.print("Sizeof VoltageProgram: ");
    Serial.println(sizeof(VoltageProgram));
    VoltageProgram *voltageProgram2 = new VoltageProgram("VoltageP2");
    Serial.println("Create voltage program 2");
    VoltageProgram *voltageProgram3 = new VoltageProgram("VoltageP3");
    Serial.println("Create voltage program 3");
    VoltageProgram *voltageProgram4 = new VoltageProgram("VoltageP4");
    Serial.println("Create voltage program 4");
    this->list[0] = voltageProgram1;
    this->list[1] = voltageProgram2;
    this->list[2] = voltageProgram3;
    this->list[3] = voltageProgram4;
    Serial.println("Add programs to list");
    this->programsCount = 4;
    Serial.println("Get list count");
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    Serial.println("Get LCD");

    lcd->setCursor(0,0);
//    lcd->print("test string");
    lcd->print(CURSOR_CHAR);
    lcd->setCursor(1, 0);
    lcd->print(((Program *)voltageProgram1)->getName());
    lcd->setCursor(1, 1);
    lcd->print(((Program *)voltageProgram2)->getName());
}

void MainMenu::loop() {
//    Serial.println("ttt");
    if(programSelected){
        programSelected = 0;
        ModManager::getManager()->getEventBus()->generateEvent(PROGRAM_RUN_EVENT, &list[selector], sizeof(Program *));
    }
    if(lastSelector != selector){

        Serial.print("Selector: ");
        Serial.println(selector);
        Serial.print("last selector: ");
        Serial.println(lastSelector);
        LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
        if(!selectorPos && lastSelector < selector){
            lcd->setCursor(0, 0);
            lcd->print(" ");
            lcd->setCursor(0, 1);
            lcd->print(CURSOR_CHAR);
            selectorPos = 1;
        }
        else if(!selectorPos && lastSelector > selectorPos){
            printProgram(lcd, 0, list[selector]);
            printProgram(lcd, 1, list[selector + 1]);

        }
        else if(selectorPos && lastSelector > selector){
            lcd->setCursor(0, 1);
            lcd->print(" ");
            lcd->setCursor(0, 0);
            lcd->print(CURSOR_CHAR);
            selectorPos = 0;
        }
        else if(selectorPos && lastSelector < selector){
//            VoltageProgram *p = (VoltageProgram*)get_list_element(items, selector - 1);
            printProgram(lcd, 0, list[selector - 1]);
//            p = (VoltageProgram *)get_list_element(items, selector);
            printProgram(lcd, 1, list[selector]);
        }
        lastSelector = selector;
    }
}

char *MainMenu::getName() {
    return "Главное меню";
}

void MainMenu::event(Event *event) {
    switch (event ->type){
        case SHORT_PUSH_KEY_EVENT:
        case LONG_PUSH_KEY_EVENT:
            switch (*((uint8_t *)event->data)){
                case BUTTON_LEFT:
                    break;
                case BUTTON_RIGHT:
                    break;
                case BUTTON_DOWN:
                    if(selector < programsCount - 1)
                        selector++;
                    break;
                case BUTTON_UP:
                    if(selector > 0)
                        selector--;
                    break;
                case BUTTON_OK:
                    programSelected = 1;
                    break;
            }
    }

}

void MainMenu::printProgram(LiquidCrystal_I2C *lcd, int position, Program *p) {
    lcd->setCursor(1, position);
    Serial.println(p->getName());
    int spacelen = 15 - strlen(p->getName());
    lcd->print(p->getName());
    if(spacelen > 0){
        for(int i = 0; i < spacelen; i++)
            lcd->print(" ");
    }
}

