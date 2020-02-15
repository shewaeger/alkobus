//
// Created by shewa on 12.02.2020.
//

#ifndef MEGA_POWER_DRIVER_MAINPROCESSPROGRAM_H
#define MEGA_POWER_DRIVER_MAINPROCESSPROGRAM_H

#include <Program.h>
#include <list_utils.h>

class AlkobusMenu;

class MainProcessProgram : public Program {
private:
    list_element * items = NULL;
    int selector;
    bool isExit;
public:

    virtual void setup();

    virtual void loop();

    virtual void event(Event *event);

    virtual char *getName();
};


#endif //MEGA_POWER_DRIVER_MAINPROCESSPROGRAM_H
