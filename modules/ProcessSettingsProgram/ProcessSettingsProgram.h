//
// Created by shewa on 12.02.2020.
//

#ifndef MEGA_POWER_DRIVER_PROCESSSETTINGSPROGRAM_H
#define MEGA_POWER_DRIVER_PROCESSSETTINGSPROGRAM_H

#include <Program.h>
class AlkobusMenu;
class EmptyProgram;
class TimeSetProgram;
class ProcessSettingsProgram : public Program {
private:
    AlkobusMenu *menu;
    bool programSelected = false;
    EmptyProgram *exitProgram;
    char * name;
    TimeSetProgram *openingDurationProgram;

public:

    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();
};


#endif //MEGA_POWER_DRIVER_PROCESSSETTINGSPROGRAM_H
