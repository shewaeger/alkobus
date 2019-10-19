//
// Created by shewa on 19.10.19.
//

#ifndef MEGA_POWER_DRIVER_MODMANAGER_H
#define MEGA_POWER_DRIVER_MODMANAGER_H

#include <list_utils.h>
#include <EventBus.h>
#include <Keyboard.h>
#include <temperature.h>
#include <voltage.h>

class ModManager {
private:
    static ModManager *manager;

    EventBus *eventBus;
    Keyboard *keyboard;
    Temperature *temperature;
    VoltageControl *voltageControl;

    ModManager();
public:
    static ModManager * getManager();

    EventBus * getEventBus();
    void setup();
    void loop();
};

#endif //MEGA_POWER_DRIVER_MODMANAGER_H