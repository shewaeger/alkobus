//
// Created by shewa on 15.02.2020.
//

#include "ExtendedTimeMessageProgram.h"
#include <AlkobusMenu.h>
#include <EventBus.h>
#include <Keyboard.h>
#include <ModManager.h>
#include <EmptyProgram.h>

void ExtendedTimeMessageProgram::setup() {
    programSelected = false;
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    menu = new AlkobusMenu(lcd);
    this->yesProgram = new EmptyProgram("Add time");
    this->noProgram = new EmptyProgram("Continue");
    menu->addProgram(noProgram);
    menu->addProgram(yesProgram);
}

void ExtendedTimeMessageProgram::loop() {
    if(programSelected){
        Program *p = menu->getCurrentProgram();
        if(p == yesProgram)
            exit(0);
        if(p == noProgram)
            exit(3);
        delete menu;
        return;
    }
    menu->loop();
}

void ExtendedTimeMessageProgram::event(Event *event) {
    switch (event->type) {
        case SHORT_PUSH_KEY_EVENT:
        case LONG_PUSH_KEY_EVENT:
            switch (*((uint8_t *) event->data)) {
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

char *ExtendedTimeMessageProgram::getName() {
    return "";
}
