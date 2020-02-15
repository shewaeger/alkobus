//
// Created by shewa on 15.02.2020.
//

#ifndef MEGA_POWER_DRIVER_DELTACORRECTIONPROGRAM_H
#define MEGA_POWER_DRIVER_DELTACORRECTIONPROGRAM_H


#include <Program.h>
#include <stddef.h>

struct Thermometer;

class DeltaCorrectionProgram : public Program {
    Thermometer *thermometer1 = NULL;
    Thermometer *thermometer2 = NULL;
    bool isExit;
public:

    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();
};


#endif //MEGA_POWER_DRIVER_DELTACORRECTIONPROGRAM_H
