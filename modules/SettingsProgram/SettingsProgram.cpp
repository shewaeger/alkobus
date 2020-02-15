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
#include <Settings.h>
#include <ProcessSettingsProgram.h>
#include <VariableSetProgram.h>
#include <TimeSetProgram.h>
#include <ValveSettingsProgram.h>
#include <FindThermometerProgram.h>

void SettingsProgram::setup() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    this->menu = new AlkobusMenu(lcd);

    exitProgram = new EmptyProgram("Save and exit");
    menu->addProgram(exitProgram);

    Settings_struct *settingsStruct = ModManager::getManager()->getSettings()->getStruct();
    Program *p;
    p = new FindThermometerProgram("Find thermometer 1", settingsStruct->thermometer1Addr);
    menu->addProgram(p);

    p = new FindThermometerProgram("Find thermometer 2", settingsStruct->thermometer2Addr);
    menu->addProgram(p);

    p = new FindThermometerProgram("Find thermometer 2", settingsStruct->thermometer2Addr);
    menu->addProgram(p);

    p = new VariableSetProgram<float>("Initial temperature", &(settingsStruct->initialTemperature), 10,
                                               70, .5);
    menu->addProgram(p);
    p = new VariableSetProgram<float>("Working voltage", &(settingsStruct->workingVoltage), 50, 190, 1);
    menu->addProgram(p);
    p = new VariableSetProgram<float>("Allowed delta", &(settingsStruct->allowedDelta), 0, 5, 0.1);
    menu->addProgram(p);
    p = new VariableSetProgram<float>("Alert temperature", &(settingsStruct->errorTemperature), 40, 80, .5);
    menu->addProgram(p);
    p = new ValveSettingsProgram(
            "Head 1 settings",
            &settingsStruct->head1Time,
            &settingsStruct->head1PWMCount,
            &settingsStruct->head1PWMScale,
            &settingsStruct->head1OpeningDuration);
    menu->addProgram(p);

    p = new ValveSettingsProgram(
            "Head 2 settings",
            &settingsStruct->head2Time,
            &settingsStruct->head2PWMCount,
            &settingsStruct->head2PWMScale,
            &settingsStruct->head2OpeningDuration);
    menu->addProgram(p);

    p = new ValveSettingsProgram(
            "Head extended settings",
            &settingsStruct->headExTime,
            &settingsStruct->headExPWMCount,
            &settingsStruct->headExPWMScale,
            &settingsStruct->headExOpeningDuration);
    menu->addProgram(p);

    p = new ValveSettingsProgram(
            "Headrest settings",
            &settingsStruct->headrestTime,
            &settingsStruct->headrestPWMCount,
            &settingsStruct->headrestPWMScale,
            &settingsStruct->headrestOpeningDuration);
    menu->addProgram(p);

    p = new ValveSettingsProgram(
            "Headrest extended settings",
            &settingsStruct->headrestExTime,
            &settingsStruct->headrestExPWMCount,
            &settingsStruct->headrestExPWMScale,
            &settingsStruct->headrestExOpeningDuration);
    menu->addProgram(p);

    p = new ProcessSettingsProgram();
    menu->addProgram(p);

}

void SettingsProgram::loop() {
    if(programSelected){
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
            ModManager::getManager()->getSettings()->saveSettings();
            break;
    }

}

char *SettingsProgram::getName() {
    return "Settings";
}
