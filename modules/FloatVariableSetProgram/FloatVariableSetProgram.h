//
// Created by shewa on 10.02.2020.
//

#ifndef MEGA_POWER_DRIVER_FLOATVARIABLESETPROGRAM_H
#define MEGA_POWER_DRIVER_FLOATVARIABLESETPROGRAM_H

#include <Program.h>

class LcdOverflowString;

class FloatVariableSetProgram : public Program{
private:
    char * name;
    float * variable;
    float minValue;
    float maxValue;
    float step;
    bool isExit;
    LcdOverflowString *lcdOverflowString;
public:
    FloatVariableSetProgram(char *name, float *variable, float minValue, float maxValue,
                            float step);
    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();

    void variableUp();
    void variableDown();


};


#endif //MEGA_POWER_DRIVER_FLOATVARIABLESETPROGRAM_H
