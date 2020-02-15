//
// Created by shewa on 15.02.2020.
//

#include <EventBus.h>
#include <AlkobusMenu.h>
#include <EmptyProgram.h>
#include <ModManager.h>
#include <Keyboard.h>
#include "SoundProgram.h"
#include <Speaker.h>
void SoundProgram::setup() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    this->menu = new AlkobusMenu(lcd);

    this->repeatProgram = new EmptyProgram("Repeat");
    menu->addProgram(continueProgram);

    if(showRepeat) {
        this->continueProgram = new EmptyProgram("Continue");
        menu->addProgram(repeatProgram);
    }

    this->exitProgram = new EmptyProgram("Exit");
    menu->addProgram(exitProgram);

    programSelected = false;
    switchSound = true;
    this->soundTime = millis();
    ModManager::getManager()->getSpeaker()->enable();
}

void SoundProgram::loop() {
    if(programSelected){
        Program *p = menu->getCurrentProgram();
        if(p == continueProgram)
            exit(0);
        if(p == repeatProgram)
            exit(2);
        if(p == exitProgram)
            exit(1);
        ModManager::getManager()->getSpeaker()->disable();
        delete menu;
        return;
    }
    if(millis() - soundTime >= 500){
        Serial.println(switchSound);
        if(switchSound)
            ModManager::getManager()->getSpeaker()->disable();
        else
            ModManager::getManager()->getSpeaker()->enable();
        switchSound = !switchSound;
        soundTime = millis();
    }
    menu->loop();
}

void SoundProgram::event(Event *event) {
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

char *SoundProgram::getName() {
    return "";
}

SoundProgram::SoundProgram(bool showRepeat) : showRepeat(showRepeat) {}
