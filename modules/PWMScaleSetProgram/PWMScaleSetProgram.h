//
// Created by shewa on 11.02.2020.
//

#ifndef MEGA_POWER_DRIVER_PWMSCALESETPROGRAM_H
#define MEGA_POWER_DRIVER_PWMSCALESETPROGRAM_H

#include <Program.h>
class LcdOverflowString;

class PWMScaleSetProgram :public Program{
private:
    bool *variable;
    LcdOverflowString *lcdOverflowString;
    bool isExit;

public:
    PWMScaleSetProgram(bool *variable);

    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();

};


#endif //MEGA_POWER_DRIVER_PWMSCALESETPROGRAM_H
