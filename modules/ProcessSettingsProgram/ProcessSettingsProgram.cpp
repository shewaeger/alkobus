//
// Created by shewa on 12.02.2020.
//

#include <ModManager.h>
#include <LiquidCrystal_I2C.h>
#include <EventBus.h>
#include <Keyboard.h>
#include <Settings.h>
#include <VariableSetProgram.h>
#include <limits.h>
#include <PWMScaleSetProgram.h>
#include <TimeSetProgram.h>
#include <AlkobusMenu.h>
#include <EmptyProgram.h>
#include "ProcessSettingsProgram.h"

void ProcessSettingsProgram::setup() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    this->menu = new AlkobusMenu(lcd);
    Settings_struct *settingsStruct = ModManager::getManager()->getSettings()->getStruct();
    Program *p = new VariableSetProgram<float>("Starting process temperature", &(settingsStruct->processTemperatureStart),
                                               60, 100, .5);
    menu->addProgram(p);
    p = new VariableSetProgram<float>("Ending process temperature", &(settingsStruct->processTemperatureEnd), 60,
                                      100, .5);
    menu->addProgram(p);

    p = new VariableSetProgram<unsigned long>("PWM count", &(settingsStruct->processPWMCount), 0, LONG_MAX, 1);
    menu->addProgram(p);
    p = new PWMScaleSetProgram(&(settingsStruct->processPWMScale));
    menu->addProgram(p);
    unsigned long openingDurationMax;
    if(settingsStruct->processPWMCount){
       openingDurationMax = (settingsStruct->processPWMScale ? 3600000 : 60000 ) / settingsStruct->processPWMCount;
    } else {
        openingDurationMax = 0;
    }
    this->openingDurationProgram = new TimeSetProgram("Opening duration on 100%", &(settingsStruct->processOpeningDuration100Percent), openingDurationMax, FORMAT_MILLIS);
    menu->addProgram(openingDurationProgram);
    p = new VariableSetProgram<unsigned char>("Percents on end", &(settingsStruct->processOpeningDurationEndPercent), 0, 100, 1);
    menu->addProgram(p);
    this->exitProgram = new EmptyProgram("Exit");
    menu->addProgram(exitProgram);

}

void ProcessSettingsProgram::loop() {
    if(programSelected){
        programSelected = false;
        Program * p = menu->getCurrentProgram();
        if(p == exitProgram){
            delete menu;
            exit();
            return;
        }
        ModManager::getManager()->getEventBus()->generateEvent(PROGRAM_RUN_EVENT, &p, sizeof(Program *));
        return;
    }
    menu->loop();
}

void ProcessSettingsProgram::event(Event *event) {
    unsigned long tmp;
    Settings_struct *settings = ModManager::getManager()->getSettings()->getStruct();
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
            if(settings->processPWMCount){
                tmp = ( settings->processPWMScale ? 3600000 : 60000 ) / settings->processPWMCount;
            } else {
                tmp = 0;
            }
            if(settings->processOpeningDuration100Percent > tmp){
                settings->processOpeningDuration100Percent = tmp;
                openingDurationProgram->setMaxTime(tmp);
            }
            ModManager::getManager()->getSettings()->saveSettings();
            break;
    }
}

char *ProcessSettingsProgram::getName() {
    return "Main program settings";
}