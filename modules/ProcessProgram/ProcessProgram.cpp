//
// Created by shewa on 15.02.2020.
//

#include "ProcessProgram.h"

void ProcessProgram::setup() {
    Program::setup();
}

void ProcessProgram::loop() {
    Program::loop();
}

void ProcessProgram::event(Event *event) {
    Program::event(event);
}

char *ProcessProgram::getName() {
    return "";
}
