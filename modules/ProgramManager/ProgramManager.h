//
// Created by shewa on 21.10.19.
//

#ifndef MEGA_POWER_DRIVER_PROGRAMMANAGER_H
#define MEGA_POWER_DRIVER_PROGRAMMANAGER_H

#include <stddef.h>

class Program;
struct list_element;
struct Event;

class ProgramManager {
    static ProgramManager *manager;

    list_element *begin = NULL;
    void onProgramRun(Event *);
    void onProgramExit(Event *);
public:
    static ProgramManager* getManager();
    void loop();
    void setup();
};


#endif //MEGA_POWER_DRIVER_PROGRAMMANAGER_H
