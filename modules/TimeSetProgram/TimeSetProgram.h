//
// Created by shewa on 10.02.2020.
//

#ifndef MEGA_POWER_DRIVER_TIMESETPROGRAM_H
#define MEGA_POWER_DRIVER_TIMESETPROGRAM_H


#include <Program.h>

class LcdOverflowString;

#define FORMAT_HOUR 1
#define FORMAT_MINUTES 3
#define FORMAT_SECONDS 7
#define FORMAT_MILLIS  15

#define FORMAT_HOUR_MASK 1
#define FORMAT_MINUTES_MASK 2
#define FORMAT_SECONDS_MASK 4
#define FORMAT_MILLIS_MASK 8


class TimeSetProgram : public Program{
private:
    unsigned char format;
    bool isExit;
    unsigned long *variable;
    char * name;
    char selector;
    unsigned long maxTime;
    void selectorLeft();
    void selectorRight();
    void buttonDown();
    void buttonUp();
public:
    virtual void setup();

    virtual void event(Event *event);

    virtual char *getName();

    TimeSetProgram(char *name, unsigned long *variable, unsigned long maxValue, unsigned char format);

    virtual void setMaxTime(unsigned long maxTime);

    virtual void loop();
};


#endif //MEGA_POWER_DRIVER_TIMESETPROGRAM_H
