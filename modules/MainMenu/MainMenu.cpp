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

    VoltageProgram *voltageProgram1 = new VoltageProgram("VoltageP111");
    VoltageProgram *voltageProgram2 = new VoltageProgram("VoltageP2222222");
    VoltageProgram *voltageProgram3 = new VoltageProgram("VoltageP33");
    VoltageProgram *voltageProgram4 = new VoltageProgram("VoltageP444");
    push_list_element(&items, &voltageProgram1, sizeof(VoltageProgram *) );
    push_list_element(&items, &voltageProgram2, sizeof(VoltageProgram *) );
    push_list_element(&items, &voltageProgram3, sizeof(VoltageProgram *) );
    push_list_element(&items, &voltageProgram4, sizeof(VoltageProgram *) );
    this->programsCount = count_list(items);
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();

    lcd->setCursor(0, 0);
    lcd->print(CURSOR_CHAR);
    lcd->setCursor(1, 0);
    lcd->print(((Program *) voltageProgram1)->getName());
    lcd->setCursor(1, 1);
    lcd->print(((Program *) voltageProgram2)->getName());
}

void MainMenu::loop() {
//    Serial.println("ttt");
    if (programSelected) {
        programSelected = 0;
        Program **childProgram = (Program **)get_list_element(items, selector);
        ModManager::getManager()->getEventBus()->generateEvent(PROGRAM_RUN_EVENT, childProgram, sizeof(Program *));
    }
    if (lastSelector != selector) {

        LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
        if (!selectorPos && lastSelector < selector) {
            lcd->setCursor(0, 0);
            lcd->print(" ");
            lcd->setCursor(0, 1);
            lcd->print(CURSOR_CHAR);
            selectorPos = 1;
        } else if (!selectorPos && lastSelector > selectorPos) {
            Program **p = (Program **)get_list_element(items, selector);
            printProgram(lcd, 0, *p);
            p = (Program **)get_list_element(items, selector + 1);
            printProgram(lcd, 1, *p);

        } else if (selectorPos && lastSelector > selector) {
            lcd->setCursor(0, 1);
            lcd->print(" ");
            lcd->setCursor(0, 0);
            lcd->print(CURSOR_CHAR);
            selectorPos = 0;
        } else if (selectorPos && lastSelector < selector) {
            Program **p = (Program**)get_list_element(items, selector - 1);
            printProgram(lcd, 0, *p);
            p = (Program **)get_list_element(items, selector);
            printProgram(lcd, 1, *p);
        }
        lastSelector = selector;
    }
}

char *MainMenu::getName() {
    return "Главное меню";
}

void MainMenu::event(Event *event) {
    switch (event->type) {
        case SHORT_PUSH_KEY_EVENT:
        case LONG_PUSH_KEY_EVENT:
            switch (*((uint8_t *) event->data)) {
                case BUTTON_LEFT:
                    break;
                case BUTTON_RIGHT:
                    break;
                case BUTTON_DOWN:
                    if (selector < programsCount - 1)
                        selector++;
                    break;
                case BUTTON_UP:
                    if (selector > 0)
                        selector--;
                    break;
                case BUTTON_OK:
                    programSelected = 1;
                    break;
            }
            break;
        case CHILD_EXIT_EVENT:
            lastSelector += selectorPos ? -1 : 1;
            break;
    }

}

void MainMenu::printProgram(LiquidCrystal_I2C *lcd, int position, Program *p) {
    lcd->setCursor(1, position);
    int spacelen = 15 - strlen(p->getName());
    lcd->print(p->getName());
    if (spacelen > 0) {
        for (int i = 0; i < spacelen; i++)
            lcd->print(" ");
    }
}

