//
// Created by shewa on 21.10.19.
//

#ifndef MEGA_POWER_DRIVER_PROGRAMMANAGER_H
#define MEGA_POWER_DRIVER_PROGRAMMANAGER_H

class MainMenu;

class ProgramManager {
    static ProgramManager *manager;

    MainMenu * menu;
public:
    static ProgramManager* getManager();
    void loop();
    void setup();
};


#endif //MEGA_POWER_DRIVER_PROGRAMMANAGER_H
