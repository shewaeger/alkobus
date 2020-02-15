//
// Created by shewa on 15.02.2020.
//

#ifndef MEGA_POWER_DRIVER_PROCESSPROGRAM_H
#define MEGA_POWER_DRIVER_PROCESSPROGRAM_H


#include <Program.h>

struct Thermometer;

class ProcessProgram : public Program {
    bool firstStep = true;
    bool isWrongDelta = false;
    unsigned long timeStart;
    Thermometer *thermometer1;
    Thermometer *thermometer2;
    unsigned long od100; // openingDuration start;
    unsigned long odEnd; //openingDuration end;
    float pte; // process temperature end
    float pts; //Process temperature start
    float k;
    float b;
    void calculateCoefficients();
public:

    virtual void drawScreen();

    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();
};


#endif //MEGA_POWER_DRIVER_PROCESSPROGRAM_H
