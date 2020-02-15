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

void MainProcessProgram::setup() {
    Settings_struct *settings = ModManager::getManager()->getSettings()->getStruct();
    selector = 0;
    isExit = false;
    Program *p;
    //Selector = 0
    p = new VariableSetProgram<float>("Set starting temperature", &(settings->processTemperatureStart),
                                      30, 90, .5);
    push_list_element(&this->items, &p, sizeof(Program *));

    //Selector = 2
    p = new WarmingUpProgram();
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 3
    p = new SoundProgram();
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
    p = new SoundProgram();
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
    p = new SoundProgram();
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 10
    p = new PrimarySelectionSettingsProgram(
            &(settings->headExTime),
            &(settings->headExPWMCount),
            &(settings->headExPWMScale),
            &(settings->headExOpeningDuration));
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 11
    p = new PrimarySelectionProgram(
            &(settings->headExTime),
            &(settings->headExPWMCount),
            &(settings->headExPWMScale),
            &(settings->headExOpeningDuration));
    push_list_element(&this->items, &p, sizeof(Program *));
    //Selector = 12
    p = new SoundProgram();
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
    Serial.println("NextProgram");
    Program *p = *(Program **) get_list_element(items, selector);
    ModManager::getManager()->getEventBus()->generateEvent(PROGRAM_RUN_EVENT, &p, sizeof(Program *));
}

void MainProcessProgram::event(Event *event) {
    if (event->type == CHILD_EXIT_EVENT) {
        Program *p = (Program *)event->data;
        switch (p->getExitCode()) {
            case 0:
                selector++;
                break;
            case 1: // необходимо выйти из программы
                isExit = true;
                break;
            case 2:
                break; // Повторить программу
        }
        Serial.print("Exit code: ");
        Serial.println((unsigned long)p, HEX);
    }
}

char *MainProcessProgram::getName() {
    return "Start process";
}
