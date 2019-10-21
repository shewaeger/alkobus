//
// Created by shewa on 21.10.19.
//

#include "Program.h"
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

void Program::exit() {
    Program * program = this;
    ModManager::getManager()->getEventBus()->generateEvent(PROGRAM_EXIT_EVENT, &program, sizeof(program));
}

Program::~Program() {

}
