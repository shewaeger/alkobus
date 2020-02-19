//
// Created by shewa on 19.10.19.
//

#ifndef MEGA_POWER_DRIVER_MODMANAGER_H
#define MEGA_POWER_DRIVER_MODMANAGER_H

class EventBus;
class Keyboard;
class Temperature;
class VoltageControl;
class LiquidCrystal_I2C;
class Valve;
class Settings;
class TenSwitch;
class Speaker;
class ModManager {
private:
    static ModManager *manager;

    EventBus *eventBus;
    Keyboard *keyboard;
    Temperature *temperature;
    VoltageControl *voltageControl;
    LiquidCrystal_I2C *lcd;
    Valve *valve;
    Settings *settings;
    TenSwitch *tenSwitch;
    Speaker * speaker;
    Valve * mainRelay;
    ModManager();

public:
    static ModManager * getManager();
    EventBus * getEventBus();
    LiquidCrystal_I2C * getLCD();
    Temperature * getThermometers();
    VoltageControl * getVoltageControl();
    Valve *getValve();
    Valve *getMainRelay();
    Settings *getSettings();
    TenSwitch *getTenSwitch();
    Speaker *getSpeaker();

    void setup();

    void loop();
};

#endif //MEGA_POWER_DRIVER_MODMANAGER_H
