//
// Created by shewa on 21.10.19.
//

#ifndef MEGA_POWER_DRIVER_PROGRAM_H
#define MEGA_POWER_DRIVER_PROGRAM_H

struct Event;

class Program {

public:
    Program();
    virtual ~Program();
    virtual void backgroundLoop();
    virtual void setup();
    virtual void loop();
    virtual void event(Event *);
    virtual char * getName() = 0;
    void exit();
};


#endif //MEGA_POWER_DRIVER_PROGRAM_H
