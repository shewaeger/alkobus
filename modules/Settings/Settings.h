//
// Created by shewa on 02.02.20.
//

#ifndef MEGA_POWER_DRIVER_SETTINGS_H
#define MEGA_POWER_DRIVER_SETTINGS_H


#include <inttypes.h>

struct Settings_struct {
    uint8_t thermometer1Addr[8];
    uint8_t thermometer2Addr[8];
    uint8_t thermometer3Addr[8];
    float initialTemperature;
    float workingVoltage;
    float allowedDelta;
    unsigned long head1Time;
    unsigned long head1PWMCount;
    bool head1PWMScale;
    unsigned long head1OpeningDuration;
    unsigned long head2Time;
    unsigned long head2PWMCount;
    bool head2PWMScale;
    unsigned long head2OpeningDuration;
    unsigned long headExTime;
    unsigned long headExPWMCount;
    bool headExPWMScale;
    unsigned long headExOpeningDuration;
    unsigned long headrestTime;
    unsigned long headrestPWMCount;
    bool headrestPWMScale;
    unsigned long headrestOpeningDuration;
    unsigned long headrestExTime;
    unsigned long headrestExPWMCount;
    bool headrestExPWMScale;
    unsigned long headrestExOpeningDuration;
    float processTemperatureStart;
    float processTemperatureEnd;
    float errorTemperature;
    unsigned long processPWMCount;
    bool processPWMScale;
    unsigned long processOpeningDuration100Percent;
    uint8_t processOpeningDurationEndPercent;
};

class Settings {
    Settings_struct settings;
public:
    Settings();

    void saveSettings();

    Settings_struct *getStruct();

};


#endif //MEGA_POWER_DRIVER_SETTINGS_H
