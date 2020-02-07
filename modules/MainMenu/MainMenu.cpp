//
// Created by shewa on 21.10.19.
//

#include "MainMenu.h"
#include <AlkobusMenu.h>
#include <Arduino.h>
#include <ModManager.h>
#include <LiquidCrystal_I2C.h>
#include <Keyboard.h>
#include <VoltageProgram.h>
#include <list_utils.h>

MainMenu::MainMenu() : Program() {

}

MainMenu::~MainMenu() {

}

void MainMenu::backgroundLoop() {
    Program::backgroundLoop();
}

void MainMenu::setup() {
    VoltageProgram *voltageProgram1 = new VoltageProgram("VoltageP111");
    VoltageProgram *voltageProgram2 = new VoltageProgram("Select main program123456789");
    VoltageProgram *voltageProgram3 = new VoltageProgram("VoltageP33");
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();

    menu = new AlkobusMenu(lcd);
    menu->addProgram(voltageProgram1);
    menu->addProgram(voltageProgram2);
    menu->addProgram(voltageProgram3);
}

void MainMenu::loop() {
    if(programSelected){
        programSelected = false;
        Program * p = menu->getCurrentProgram();
        ModManager::getManager()->getEventBus()->generateEvent(PROGRAM_RUN_EVENT, &p, sizeof(Program *));
        return;
    }
    menu->loop();
}

char *MainMenu::getName() {
    return "Main menu";
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
                    menu->selectorDown();
                    break;
                case BUTTON_UP:
                    menu->selectorUp();
                    break;
                case BUTTON_OK:
                    programSelected = true;
                    break;
            }
            break;
        case CHILD_EXIT_EVENT:
            break;
    }

}


