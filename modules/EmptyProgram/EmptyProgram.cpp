//
// Created by shewa on 07.02.2020.
//

#include "EmptyProgram.h"

char *EmptyProgram::getName() {
    return this->name;
}

EmptyProgram::EmptyProgram(char *name) {
    this->name = name;
}
