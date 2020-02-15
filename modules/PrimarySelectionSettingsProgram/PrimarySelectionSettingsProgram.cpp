//
// Created by shewa on 13.02.2020.
//

#include "PrimarySelectionSettingsProgram.h"
#include <AlkobusMenu.h>
#include <ModManager.h>
#include <EventBus.h>
#include <Keyboard.h>
#include <ValveSettingsProgram.h>
#include <Settings.h>
#include <EmptyProgram.h>

void PrimarySelectionSettingsProgram::setup() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    this->menu = new AlkobusMenu(lcd);

    exitProgram = new EmptyProgram("Continue");
    menu->addProgram(exitProgram);
    Program *p = new ValveSettingsProgram(
            "Change settings?",
            processTime,
            pwmCount,
            pwmScale,
            openingDuration);
    menu->addProgram(p);
}

void PrimarySelectionSettingsProgram::loop() {
    if(programSelected) {
        programSelected = false;
        Program * p = menu->getCurrentProgram();
        if(p == exitProgram){
            delete menu;
            exit(0);
            return;
        }
        ModManager::getManager()->getEventBus()->generateEvent(PROGRAM_RUN_EVENT, &p, sizeof(Program *));
        return;
    }
    menu->loop();
}

void PrimarySelectionSettingsProgram::event(Event *event) {
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
    }
}

char *PrimarySelectionSettingsProgram::getName() {
    return "";
}

PrimarySelectionSettingsProgram::PrimarySelectionSettingsProgram(unsigned long *processTime, unsigned long *pwmCount,
                                                                 bool *pwmScale, unsigned long *openingDuration):
                                                                 processTime(processTime),
                                                                 pwmScale(pwmScale),
                                                                 pwmCount(pwmCount),
                                                                 openingDuration(openingDuration){}
