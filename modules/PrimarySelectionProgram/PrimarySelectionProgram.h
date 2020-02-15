//
// Created by shewa on 13.02.2020.
//

#ifndef MEGA_POWER_DRIVER_PRIMARYSELECTIONPROGRAM_H
#define MEGA_POWER_DRIVER_PRIMARYSELECTIONPROGRAM_H


#include <Program.h>

class PrimarySelectionProgram : public Program {
private:
    unsigned long processStarting;
    unsigned long *processTime;
    unsigned long *pwmCount;
    bool *pwmScale;
    unsigned long *openingDuration;
    bool isExit;
    char timeShowBuffer[32];
    void generateLeftTime();
    void drawScreen();

public:
    PrimarySelectionProgram(unsigned long *processTime, unsigned long *pwmCount, bool *pwmScale,
                            unsigned long *openingDuration);

    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();

};


#endif //MEGA_POWER_DRIVER_PRIMARYSELECTIONPROGRAM_H
