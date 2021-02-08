//
// Created by shewa on 26.10.19.
//

#ifndef MEGA_POWER_DRIVER_TEMPERATUREPROGRAM_H
#define MEGA_POWER_DRIVER_TEMPERATUREPROGRAM_H


#include <Program.h>
#include <stddef.h>

struct list_element;

class TemperatureProgram : public Program{
private:
    list_element * thermometers;
    size_t currentThermometer = 0;
public:
    virtual ~TemperatureProgram();

    virtual void backgroundLoop();

    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);
};


#endif //MEGA_POWER_DRIVER_TEMPERATUREPROGRAM_H
