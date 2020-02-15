//
// Created by shewa on 15.02.2020.
//

#ifndef MEGA_POWER_DRIVER_SOUNDPROGRAM_H
#define MEGA_POWER_DRIVER_SOUNDPROGRAM_H


#include <Program.h>
class AlkobusMenu;

class SoundProgram : public Program{
    AlkobusMenu * menu;
    Program *repeatProgram;
    Program *exitProgram;
    Program *continueProgram;
    bool programSelected;
    unsigned long soundTime;
    bool switchSound;

public:
    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();

};


#endif //MEGA_POWER_DRIVER_SOUNDPROGRAM_H
