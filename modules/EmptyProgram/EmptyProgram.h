//
// Created by shewa on 07.02.2020.
//

#ifndef MEGA_POWER_DRIVER_EMPTYPROGRAM_H
#define MEGA_POWER_DRIVER_EMPTYPROGRAM_H

#include <Program.h>

class EmptyProgram : public Program {
private:
    char *name;
public:
    EmptyProgram(char * name);
    virtual char *getName();
};


#endif //MEGA_POWER_DRIVER_EMPTYPROGRAM_H
