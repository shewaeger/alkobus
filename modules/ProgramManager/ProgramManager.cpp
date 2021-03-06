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
#include <list_utils.h>
#include <VoltageProgram.h>

ProgramManager *ProgramManager::manager = NULL;

ProgramManager *ProgramManager::getManager() {
    if (!manager)
        manager = new ProgramManager();
    return manager;
}

void ProgramManager::loop() {
    ModManager *manager = ModManager::getManager();
    EventBus *bus = manager->getEventBus();
    Event *event;
    while ((event = bus->getLastEvent()) != NULL) {
//        Serial.print("Event address: ");
//        Serial.println((unsigned int)event, HEX);
        if (event->type == PROGRAM_RUN_EVENT) {
            onProgramRun(event);
        } else if (event->type == PROGRAM_EXIT_EVENT) {
            onProgramExit(event);
        } else {
            Program *program = *(Program **) get_last_element(this->begin);
            if (program != NULL) {
                program->event(event);
            }
        }
        bus->removeEvent(event);
    }
    size_t count = count_list(this->begin);
    for (int i = count - 1; i >= 0; i--) {
        Program *program = *(Program **) get_list_element(this->begin, i);
        if (count - 1 == i)
            program->loop();
        else
            program->backgroundLoop();
    }

}

void ProgramManager::setup() {
    ModManager *manager = ModManager::getManager();
    LiquidCrystal_I2C *lcd = manager->getLCD();
    lcd->clear();
    Serial.println("Starting Main menu...");
    Program *p = new MainMenu();
    p->setup();
    Serial.println("Main menu started");
    push_list_element(&this->begin, &p, sizeof(Program *));
}

void ProgramManager::onProgramRun(Event *event) {
    Program *nextProgram = *(Program **) event->data;
    Serial.println("Getting new program");
    nextProgram->setup();
    Serial.println("Setup new program");
    Serial.print("Program: ");
    Serial.println((unsigned long int)nextProgram, HEX);
    push_list_element(&this->begin, &nextProgram, sizeof(Program *));
}

void ProgramManager::onProgramExit(Event *event) {
    Program *program = *(Program **) event->data;
    if (program == *(Program **) get_list_element(this->begin, 0)) {
        return;
    }
    Serial.print("Exit program: ");
    Serial.println((unsigned long int) program, HEX);

    Event exitEvent;
    exitEvent.type = CHILD_EXIT_EVENT;
    exitEvent.data = program;

    list_element *el;
    int i;
    for (el = this->begin, i = 0; el != NULL; el = el->next, i++) {
        if (*(Program **) el->data == program)
            break;
    }
    if (el == NULL)
        return;

    Program *parent = *(Program **) el->prev->data;
    remove_list_element(&this->begin, i);
    parent->event(&exitEvent);
}
