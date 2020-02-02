//
// Created by shewa on 02.02.20.
//

#ifndef MEGA_POWER_DRIVER_SETTINGS_H
#define MEGA_POWER_DRIVER_SETTINGS_H


#include <inttypes.h>

class Settings {
    void getThermometer1Addr(uint8_t * addr);
    void setThermometer1Addr(uint8_t * addr);

    void getThermometer2Addr(uint8_t * addr);
    void setThermometer2Addr(uint8_t * addr);

    void getThermometer3Addr(uint8_t * addr);
    void setThermometer3Addr(uint8_t * addr);

    float getInitialTemperature();
    void setInitialTemperature(float temperature);

    float getWorkingVoltage();
    void setWorkingVoltage(float voltage);

    float getAllowableDelta();
    void setAllowableDelta(float delta);
};


#endif //MEGA_POWER_DRIVER_SETTINGS_H
