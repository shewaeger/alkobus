//
// Created by shewa on 07.02.2020.
//

#ifndef MEGA_POWER_DRIVER_SETTINGSPROGRAM_H
#define MEGA_POWER_DRIVER_SETTINGSPROGRAM_H

#include <Program.h>

class AlkobusMenu;
class EmptyProgram;
class SettingsProgram : public Program {
private:
    AlkobusMenu *menu;
    bool programSelected = false;
    EmptyProgram *exitProgram;
public:

    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();
};


#endif //MEGA_POWER_DRIVER_SETTINGSPROGRAM_H
