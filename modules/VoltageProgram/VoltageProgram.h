//
// Created by shewa on 25.10.19.
//

#ifndef MEGA_POWER_DRIVER_VOLTAGEPROGRAM_H
#define MEGA_POWER_DRIVER_VOLTAGEPROGRAM_H

#include <stdint-gcc.h>
#include "Program.h"

class VoltageProgram : public Program {
private:
    double voltage;
    uint64_t voltageCounter;

    int currentLine;
public:

    virtual void backgroundLoop();

    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);
};


#endif //MEGA_POWER_DRIVER_VOLTAGEPROGRAM_H
