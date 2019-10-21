//
// Created by shewa on 21.10.19.
//

#include "ProgramManager.h"
#include <Arduino.h>
#include <ModManager.h>
#include <EventBus.h>
#include <LiquidCrystal_I2C.h>
#include <stddef.h>
#include <MainMenu.h>

ProgramManager* ProgramManager::manager = NULL;

ProgramManager *ProgramManager::getManager() {
    if(!manager)
        manager = new ProgramManager();
    return manager;
}

void ProgramManager::loop() {
    ModManager *manager = ModManager::getManager();
    EventBus* bus = manager->getEventBus();
    Event *event;
    while(( event = bus->getLastEvent()) != NULL){
        switch (event->type){
            case PROGRAM_RUN_EVENT:
                //TODO: action on run_event
                break;
            case PROGRAM_EXIT_EVENT:
                //TODO: action on exit_event
                break;
            default: {
                this->menu->event(event);
            }
        }

        bus->removeEvent(event);
    }
}

void ProgramManager::setup() {
    ModManager *manager = ModManager::getManager();
    LiquidCrystal_I2C * lcd = manager->getLCD();
    lcd->clear();
    this->menu = new MainMenu;
    this->menu->setup();
}
