//
// Created by shewa on 13.02.2020.
//

#ifndef MEGA_POWER_DRIVER_WARMINGUPPROGRAM_H
#define MEGA_POWER_DRIVER_WARMINGUPPROGRAM_H

#include <Program.h>
#include <temperature.h>

struct Thermometer;
class WarmingUpProgram : public Program {
    unsigned long processStarting;
    Thermometer *thermometer;
    bool isExit;
public:

    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();

};


#endif //MEGA_POWER_DRIVER_WARMINGUPPROGRAM_H
