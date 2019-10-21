//
// Created by shewa on 21.10.19.
//

#ifndef MEGA_POWER_DRIVER_MAINMENU_H
#define MEGA_POWER_DRIVER_MAINMENU_H

#include <EventBus.h>
#include <Program.h>

class MainMenu : public Program{
public:
    MainMenu();

    ~MainMenu() override;

    void backgroundLoop() override;

    void setup() override;

    void loop() override;

    void event(Event *event) override;

    void exit() override;

public:

};


#endif //MEGA_POWER_DRIVER_MAINMENU_H
