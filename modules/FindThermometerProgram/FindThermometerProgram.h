//
// Created by shewa on 15.02.2020.
//

#ifndef MEGA_POWER_DRIVER_FINDTHERMOMETERPROGRAM_H
#define MEGA_POWER_DRIVER_FINDTHERMOMETERPROGRAM_H


#include <Program.h>

class FindThermometerProgram : public Program {
private:
    bool isOk;
    bool found;
    bool isFounding;
    bool isExit;
    char * name;
    uint8_t * addr;
public:
    FindThermometerProgram(char *name, uint8_t *addr);
    virtual void drawScreen();
    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();
};


#endif //MEGA_POWER_DRIVER_FINDTHERMOMETERPROGRAM_H
