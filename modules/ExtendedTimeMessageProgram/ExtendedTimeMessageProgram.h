//
// Created by shewa on 15.02.2020.
//

#ifndef MEGA_POWER_DRIVER_EXTENDEDTIMEMESSAGEPROGRAM_H
#define MEGA_POWER_DRIVER_EXTENDEDTIMEMESSAGEPROGRAM_H

#include <Program.h>
class AlkobusMenu;

class ExtendedTimeMessageProgram : public Program {
    Program *yesProgram;
    Program *noProgram;
    AlkobusMenu *menu;
    bool programSelected;
public:

    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();
};


#endif //MEGA_POWER_DRIVER_EXTENDEDTIMEMESSAGEPROGRAM_H
