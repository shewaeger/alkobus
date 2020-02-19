//
// Created by shewa on 12.02.2020.
//

#include "MainProcessProgram.h"
#include <Keyboard.h>
#include <EventBus.h>
#include <AlkobusMenu.h>
#include <ModManager.h>
#include <EmptyProgram.h>
#include <Settings.h>
#include <PrimarySelectionSettingsProgram.h>
#include <PrimarySelectionProgram.h>
#include <WarmingUpProgram.h>
#include <VariableSetProgram.h>
#include <SoundProgram.h>
#include <DeltaCorrectionProgram.h>
#include <ExtendedTimeMessageProgram.h>
#include <ProcessSettingsProgram.h>
#include <ProcessProgram.h>
#include <Speaker.h>
#include <Valve.h>
#include <voltage.h>
#include <TenSwitch.h>

void MainProcessProgram::setup() {
    selector = 0;
    isExit = false;
    ModManager::getManager()->getMainRelay()->open();
}

void MainProcessProgram::loop() {

    if(selector >= 24 || isExit){
        ModManager::getManager()->getSpeaker()->disable();
        ModManager::getManager()->getValve()->disablePWM();
        ModManager::getManager()->getVoltageControl()->setVoltage(0);
        ModManager::getManager()->getTenSwitch()->disable();
        ModManager::getManager()->getMainRelay()->close();
        exit(0);
        return;
    }

    Program *p = getProgramBySelector(selector);
    Serial.print("Next program: ");
    Serial.print(selector);
    Serial.print("(selector); ");
    Serial.print((unsigned long) p, HEX);
    Serial.println("(address)");
    ModManager::getManager()->getEventBus()->generateEvent(PROGRAM_RUN_EVENT, &p, sizeof(Program *));
}

void MainProcessProgram::event(Event *event) {
    if (event->type == CHILD_EXIT_EVENT) {
        Program *p = (Program *) event->data;
        switch (p->getExitCode()) {
            case 1: // необходимо выйти из программы
                isExit = true;
                break;
            default:
                Serial.print("Selector: ");
                Serial.println((unsigned long) p, HEX);
                selector = getSelector(selector, p->getExitCode());
                break; // Повторить программу
        }
        delete p;
    }

}

char *MainProcessProgram::getName() {
    return "Start process";
}

int MainProcessProgram::getSelector(int selector, int code) {
    if (selector == 10 && code == 3) {
        return selector + 4;
    }
    if (selector == 13 && code == 2)
        return selector - 2;

    if (selector == 17 && code == 3)
        return selector + 4;

    if (selector == 20 && code == 2)
        return selector - 2;

    return selector + 1;
}

void MainProcessProgram::backgroundLoop() {
    Settings_struct *settings = ModManager::getManager()->getSettings()->getStruct();
    Thermometer *thermometer = ModManager::getManager()->getThermometers()->getThermometer(settings->thermometer3Addr);
    if (thermometer == NULL)
        return;
    if (thermometer->temperature > settings->errorTemperature) {
        Program *p = *(Program **) get_list_element(items, selector);
        p->exit(1);
    }
}

Program *MainProcessProgram::getProgramBySelector(int selector) {
    Settings_struct *settings = ModManager::getManager()->getSettings()->getStruct();
//    return new SoundProgram(false);
    switch (selector) {
        case 0:
            return new VariableSetProgram<float>("Set starting temperature", &(settings->initialTemperature),
                                                 30, 90, .5);
        case 1:
            //Selector = 1
            return new WarmingUpProgram();

        case 2:
            //Selector = 2
            return new SoundProgram(true);
        case 3:
            //Selector = 3
            return new DeltaCorrectionProgram();

        case 4:
            //Selector = 4
            return new PrimarySelectionSettingsProgram(
                    &(settings->head1Time),
                    &(settings->head1PWMCount),
                    &(settings->head1PWMScale),
                    &(settings->head1OpeningDuration));

        case 5:
            //Selector = 5
            return new PrimarySelectionProgram(
                    &(settings->head1Time),
                    &(settings->head1PWMCount),
                    &(settings->head1PWMScale),
                    &(settings->head1OpeningDuration));

        case 6:
            //Selector = 6
            return new SoundProgram(false);

        case 7:
            //Selector = 7
            return new PrimarySelectionSettingsProgram(
                    &(settings->head2Time),
                    &(settings->head2PWMCount),
                    &(settings->head2PWMScale),
                    &(settings->head2OpeningDuration));

        case 8:
            //Selector = 8
            return new PrimarySelectionProgram(
                    &(settings->head2Time),
                    &(settings->head2PWMCount),
                    &(settings->head2PWMScale),
                    &(settings->head2OpeningDuration));

        case 9:
            //Selector = 9
            return new SoundProgram(false);

        case 10:
            //Selector = 10
            return new ExtendedTimeMessageProgram();

        case 11:
            //Selector = 11
            return new PrimarySelectionSettingsProgram(
                    &(settings->headExTime),
                    &(settings->headExPWMCount),
                    &(settings->headExPWMScale),
                    &(settings->headExOpeningDuration));

        case 12:
            //Selector = 12
            return new PrimarySelectionProgram(
                    &(settings->headExTime),
                    &(settings->headExPWMCount),
                    &(settings->headExPWMScale),
                    &(settings->headExOpeningDuration));

        case 13:
            //Selector = 13
            return new SoundProgram(true);

        case 14:
            //Selector = 14
            return new PrimarySelectionSettingsProgram(
                    &(settings->headrestTime),
                    &(settings->headrestPWMCount),
                    &(settings->headrestPWMScale),
                    &(settings->headrestOpeningDuration));

        case 15:
            //Selector = 15
            return new PrimarySelectionProgram(
                    &(settings->headrestTime),
                    &(settings->headrestPWMCount),
                    &(settings->headrestPWMScale),
                    &(settings->headrestOpeningDuration));

        case 16:
            //Selector = 16
            return new SoundProgram(false);

        case 17:
            //Selector = 17
            return new ExtendedTimeMessageProgram();

        case 18:
            //Selector = 18
            return new PrimarySelectionSettingsProgram(
                    &(settings->headrestExTime),
                    &(settings->headrestExPWMCount),
                    &(settings->headrestExPWMScale),
                    &(settings->headrestExOpeningDuration));

        case 19:
            //Selector = 19
            return new PrimarySelectionProgram(
                    &(settings->headrestExTime),
                    &(settings->headrestExPWMCount),
                    &(settings->headrestExPWMScale),
                    &(settings->headrestExOpeningDuration));

        case 20:
            //Selector = 20
            return new SoundProgram(true);

        case 21:
            //Selector = 21
            return new ProcessSettingsProgram();

        case 22:
            //Selector = 22
            return new ProcessProgram();
        case 23:;
            //Selector = 23
            return new SoundProgram(false);
    }
}
