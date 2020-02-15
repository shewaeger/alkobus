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

void MainProcessProgram::setup() {
    Settings_struct *settings = ModManager::getManager()->getSettings()->getStruct();
    selector = 0;
    isExit = false;
    Program *p;
    //Selector = 0
    p = new VariableSetProgram<float>("Set starting temperature", &(settings->processTemperatureStart),
                                      30, 90, .5);
    push_list_element(&this->items, &p, sizeof(Program *));

    //Selector = 1
    p = new WarmingUpProgram();
    push_list_element(&this->items, &p, sizeof(Program *));

    //Selector = 2
    p = new SoundProgram(false);
    push_list_element(&this->items, &p, sizeof(Program *));

    //Selector = 3
    p = new DeltaCorrectionProgram();
    push_list_element(&this->items, &p, sizeof(Program *));

    //Selector = 4
    p = new PrimarySelectionSettingsProgram(
            &(settings->head1Time),
            &(settings->head1PWMCount),
            &(settings->head1PWMScale),
            &(settings->head1OpeningDuration));
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 5
    p = new PrimarySelectionProgram(
            &(settings->head1Time),
            &(settings->head1PWMCount),
            &(settings->head1PWMScale),
            &(settings->head1OpeningDuration));
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 6
    p = new SoundProgram(false);
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 7
    p = new PrimarySelectionSettingsProgram(
            &(settings->head2Time),
            &(settings->head2PWMCount),
            &(settings->head2PWMScale),
            &(settings->head2OpeningDuration));
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 8
    p = new PrimarySelectionProgram(
            &(settings->head2Time),
            &(settings->head2PWMCount),
            &(settings->head2PWMScale),
            &(settings->head2OpeningDuration));
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 9
    p = new SoundProgram(false);
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 10
    p = new ExtendedTimeMessageProgram();
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 11
    p = new PrimarySelectionSettingsProgram(
            &(settings->headExTime),
            &(settings->headExPWMCount),
            &(settings->headExPWMScale),
            &(settings->headExOpeningDuration));
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 12
    p = new PrimarySelectionProgram(
            &(settings->headExTime),
            &(settings->headExPWMCount),
            &(settings->headExPWMScale),
            &(settings->headExOpeningDuration));
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 13
    p = new SoundProgram(true);
    push_list_element(&this->items, &p, sizeof(Program *));

    //Selector = 14
    p = new PrimarySelectionSettingsProgram(
            &(settings->headrestTime),
            &(settings->headrestPWMCount),
            &(settings->headrestPWMScale),
            &(settings->headrestOpeningDuration));
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 15
    p = new PrimarySelectionProgram(
            &(settings->headrestTime),
            &(settings->headrestPWMCount),
            &(settings->headrestPWMScale),
            &(settings->headrestOpeningDuration));
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 16
    p = new SoundProgram(false);
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 17
    p = new ExtendedTimeMessageProgram();
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 18
    p = new PrimarySelectionSettingsProgram(
            &(settings->headrestExTime),
            &(settings->headrestExPWMCount),
            &(settings->headrestExPWMScale),
            &(settings->headrestExOpeningDuration));
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 19
    p = new PrimarySelectionProgram(
            &(settings->headrestExTime),
            &(settings->headrestExPWMCount),
            &(settings->headrestExPWMScale),
            &(settings->headrestExOpeningDuration));
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 20
    p = new SoundProgram(true);
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 21
    p = new ProcessSettingsProgram();
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 22
    p = new ProcessProgram();
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 23
    p = new SoundProgram(false);
    push_list_element(&this->items, &p, sizeof(Program *));
}

void MainProcessProgram::loop() {

    if (selector >= count_list(items) || isExit) {
        while (this->items) {
            Program *p = *(Program **) get_list_element(items, 0);
            delete p;
            remove_list_element(&items, 0);
        }
        exit(0);
        return;
    }
    Program *p = *(Program **) get_list_element(items, selector);
    ModManager::getManager()->getEventBus()->generateEvent(PROGRAM_RUN_EVENT, &p, sizeof(Program *));
}

void MainProcessProgram::event(Event *event) {
    if (event->type == CHILD_EXIT_EVENT) {
        Program *p = (Program *)event->data;
        switch (p->getExitCode()) {
            case 1: // необходимо выйти из программы
                isExit = true;
                break;
            default:
                selector = getSelector(selector, p->getExitCode());
                break; // Повторить программу
        }
        Serial.print("Exit code: ");
        Serial.println((unsigned long)p, HEX);
    }
}

char *MainProcessProgram::getName() {
    return "Start process";
}

int MainProcessProgram::getSelector(int selector, int code) {
    if(selector == 10 && code == 3){
        return selector + 4;
    }
    if(selector == 13 && code == 2)
        return selector - 2;

    if(selector == 17 && code == 3)
        return selector + 4;

    if(selector == 20 && code == 2)
        return selector - 2;

    return selector + 1;
}
