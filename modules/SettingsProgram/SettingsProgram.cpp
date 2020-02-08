//
// Created by shewa on 07.02.2020.
//

#include "SettingsProgram.h"
#include <ModManager.h>
#include <LiquidCrystal_I2C.h>
#include <AlkobusMenu.h>
#include <EmptyProgram.h>
#include <EventBus.h>
#include <Keyboard.h>

void SettingsProgram::setup() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    this->menu = new AlkobusMenu(lcd);

    exitProgram = new EmptyProgram("Save and exit");
    menu->addProgram(exitProgram);
}

void SettingsProgram::loop() {
    if(programSelected){
        programSelected = false;
        Program * p = menu->getCurrentProgram();
        if(p == exitProgram){
            delete menu;
            delete exitProgram;
            exit();
            return;
        }
        ModManager::getManager()->getEventBus()->generateEvent(PROGRAM_RUN_EVENT, &p, sizeof(Program *));
        return;
    }
    menu->loop();
}

void SettingsProgram::event(Event *event) {
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

char *SettingsProgram::getName() {
    return "Settings";
}
