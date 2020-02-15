//
// Created by shewa on 25.10.19.
//

#ifndef MEGA_POWER_DRIVER_VOLTAGEPROGRAM_H
#define MEGA_POWER_DRIVER_VOLTAGEPROGRAM_H

#include <stdint-gcc.h>
#include "Program.h"

class VoltageProgram : public Program {
private:
    char * name;
    double voltage;
    uint64_t voltageCounter;
    bool valveSwitch;
    int currentLine;
public:
    VoltageProgram(char * name);
    virtual void backgroundLoop();

    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();
};


#endif //MEGA_POWER_DRIVER_VOLTAGEPROGRAM_H
