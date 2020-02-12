//
// Created by shewa on 11.02.2020.
//

#ifndef MEGA_POWER_DRIVER_VALVESETTINGSPROGRAM_H
#define MEGA_POWER_DRIVER_VALVESETTINGSPROGRAM_H

#include <Program.h>
class AlkobusMenu;
class TimeSetProgram;

class ValveSettingsProgram : public Program {
private:
    char *name;
    unsigned long *openingDuration;
    bool *pwmScale;
    unsigned long *time;
    unsigned long *pwmCount;
    AlkobusMenu *alkobusMenu;
    TimeSetProgram * openingDurationProgram;
    Program * exitProgram;
    bool programSelected;
public:

    ValveSettingsProgram(char *name, unsigned long *time, unsigned long *pwmCount, bool *pwmScale,
                         unsigned long *openingDuration);

    virtual void setup();

    virtual void loop();

    virtual char *getName();

    virtual void event(Event *event);

};


#endif //MEGA_POWER_DRIVER_VALVESETTINGSPROGRAM_H
