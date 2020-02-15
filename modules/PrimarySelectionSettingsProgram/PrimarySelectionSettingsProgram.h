//
// Created by shewa on 13.02.2020.
//

#ifndef MEGA_POWER_DRIVER_PRIMARYSELECTIONSETTINGSPROGRAM_H
#define MEGA_POWER_DRIVER_PRIMARYSELECTIONSETTINGSPROGRAM_H


#include <Program.h>

class AlkobusMenu;

class PrimarySelectionSettingsProgram : public Program {
private:
    AlkobusMenu *menu;
    unsigned long *processTime;
    unsigned long *pwmCount;
    bool *pwmScale;
    unsigned long *openingDuration;
    Program * exitProgram;
    bool programSelected;
public:
    PrimarySelectionSettingsProgram(unsigned long * processTime, unsigned long * pwmCount, bool *pwmScale,
                                    unsigned long * openingDuration);
    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();
};


#endif //MEGA_POWER_DRIVER_PRIMARYSELECTIONSETTINGSPROGRAM_H
