//
// Created by shewa on 21.10.19.
//

#include "Program.h"
#include <Arduino.h>
#include <ModManager.h>
#include <EventBus.h>
#include <LiquidCrystal_I2C.h>

Program::Program() {
}

void Program::backgroundLoop() {
    //Function to run in background;
}

void Program::setup() {
    ModManager::getManager()->getLCD()->setCursor(0, 1);
    ModManager::getManager()->getLCD()->print("hello_program");
}

void Program::loop() {
    // Main loop of program
}

void Program::event(Event *) {
    // Event listener
}

void Program::exit(int retValue) {
    Program *p = this;
    this->exitCode = retValue;
    ModManager::getManager()->getEventBus()->generateEvent(PROGRAM_EXIT_EVENT, &p, sizeof(Program *));
}

Program::~Program() {

}

int Program::getExitCode() {
    return this->exitCode;
}
