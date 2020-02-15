//
// Created by shewa on 21.10.19.
//

#ifndef MEGA_POWER_DRIVER_PROGRAM_H
#define MEGA_POWER_DRIVER_PROGRAM_H

struct Event;

class Program {
    int exitCode;
public:
    Program();
    virtual ~Program();
    virtual void backgroundLoop();
    virtual void setup();
    virtual void loop();
    virtual void event(Event *);
    virtual char * getName() = 0;
    void exit(int retValue);
    int getExitCode();
};


#endif //MEGA_POWER_DRIVER_PROGRAM_H
