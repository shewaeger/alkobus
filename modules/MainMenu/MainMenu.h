//
// Created by shewa on 21.10.19.
//

#ifndef MEGA_POWER_DRIVER_MAINMENU_H
#define MEGA_POWER_DRIVER_MAINMENU_H

#include <EventBus.h>
#include <Program.h>
#include <LiquidCrystal_I2C.h>


struct list_element;
class AlkobusMenu;

class MainMenu : public Program{
private:

    AlkobusMenu *menu;
    bool programSelected;
public:
    MainMenu();

    ~MainMenu() override;
    virtual void backgroundLoop() override;

    virtual void setup() override;

    virtual void loop() override;

    virtual void event(Event *event) override;

    virtual char *getName();

public:

};


#endif //MEGA_POWER_DRIVER_MAINMENU_H
