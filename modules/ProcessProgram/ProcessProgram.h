//
// Created by shewa on 15.02.2020.
//

#ifndef MEGA_POWER_DRIVER_PROCESSPROGRAM_H
#define MEGA_POWER_DRIVER_PROCESSPROGRAM_H


#include <Program.h>

class ProcessProgram : public Program {
    bool firstStep = true;
public:
    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();
};


#endif //MEGA_POWER_DRIVER_PROCESSPROGRAM_H
