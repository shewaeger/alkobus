//
// Created by shewa on 21.10.19.
//

#ifndef MEGA_POWER_DRIVER_MAINMENU_H
#define MEGA_POWER_DRIVER_MAINMENU_H

#include <EventBus.h>
#include <Program.h>
#include <LiquidCrystal_I2C.h>

struct list_element;

class MainMenu : public Program{
private:
    Program * list[4];
    int selector;
    char selectorPos;
    int lastSelector;
    bool redrawScreen;
    bool programSelected;
    int programsCount;
    bool bufferSwitch;
    void printProgram(LiquidCrystal_I2C *lcd, int position, Program * p);
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
