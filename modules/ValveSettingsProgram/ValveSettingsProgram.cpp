//
// Created by shewa on 11.02.2020.
//
#include <Arduino.h>
#include <AlkobusMenu.h>
#include <ModManager.h>

#include <Keyboard.h>
#include <VariableSetProgram.h>
#include <TimeSetProgram.h>
#include <EventBus.h>
#include <ValveSettingsProgram.h>
#include <Settings.h>
#include <PWMScaleSetProgram.h>
#include <EmptyProgram.h>
#include <limits.h>

ValveSettingsProgram::ValveSettingsProgram(char *name, unsigned long *time, unsigned long *pwmCount, bool *pwmScale,
                                           unsigned long *openingDuration) {
    this->name = name;
    this->time = time;
    this->pwmCount = pwmCount;
    this->pwmScale = pwmScale;
    this->openingDuration = openingDuration;
    programSelected = false;
}

void ValveSettingsProgram::setup() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    this->alkobusMenu = new AlkobusMenu(lcd);
    Program *p = new TimeSetProgram("Process time", this->time, LONG_MAX, FORMAT_MINUTES);
    alkobusMenu->addProgram(p);
    p = new VariableSetProgram<unsigned long>("PWM count", this->pwmCount, 0, LONG_MAX, 1);
    alkobusMenu->addProgram(p);
    p = new PWMScaleSetProgram(this->pwmScale);
    alkobusMenu->addProgram(p);
    unsigned long openingDurationMax;
    if(*pwmCount) {
        openingDurationMax = (*this->pwmScale ? 3600000 : 60000) / *(this->pwmCount);
    } else {
        openingDurationMax = 0;
    }
    this->openingDurationProgram = new TimeSetProgram("Opening duration", this->openingDuration, openingDurationMax, FORMAT_MILLIS);
    alkobusMenu->addProgram(openingDurationProgram);
    this->exitProgram = new EmptyProgram("Exit");
    alkobusMenu->addProgram(exitProgram);
}

void ValveSettingsProgram::loop() {
    if(programSelected){
        programSelected = false;
        Program * p = alkobusMenu->getCurrentProgram();
        if(p == exitProgram){
            delete alkobusMenu;
            exit();
            return;
        }
        ModManager::getManager()->getEventBus()->generateEvent(PROGRAM_RUN_EVENT, &p, sizeof(Program *));
        return;
    }
    alkobusMenu->loop();
}

void ValveSettingsProgram::event(Event *event) {
    unsigned long tmp;
    switch (event->type) {
        case SHORT_PUSH_KEY_EVENT:
        case LONG_PUSH_KEY_EVENT:
            switch (*((uint8_t *) event->data)) {
                case BUTTON_LEFT:
                    break;
                case BUTTON_RIGHT:
                    break;
                case BUTTON_DOWN:
                    alkobusMenu->selectorDown();
                    break;
                case BUTTON_UP:
                    alkobusMenu->selectorUp();
                    break;
                case BUTTON_OK:
                    programSelected = true;
                    break;
            }
            break;
        case CHILD_EXIT_EVENT:
            if(*pwmCount) {
                tmp = (*this->pwmScale ? 3600000 : 60000) / *pwmCount;
            } else {
                tmp = 0;
            }
            if(*openingDuration > tmp){
                *openingDuration = tmp;
                openingDurationProgram->setMaxTime(tmp);
            }
            ModManager::getManager()->getSettings()->saveSettings();
            break;
    }
}

char *ValveSettingsProgram::getName() {
    return this->name;
}
