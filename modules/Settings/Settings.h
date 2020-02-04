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
   uint64_t head1Time;
   uint64_t head1PWMCount;
   bool head1PWMScale;
   uint64_t head1OpeningDuration;
    uint64_t head2Time;
    uint64_t head2PWMCount;
    bool head2PWMScale;
    uint64_t head2OpeningDuration;
    uint64_t headExTime;
    uint64_t headExPWMCount;
    bool headExPWMScale;
    uint64_t headExOpeningDuration;
    uint64_t headrestTime;
    uint64_t headrestPWMCount;
    bool headrestPWMScale;
    uint64_t headrestOpeningDuration;
    uint64_t headrestExTime;
    uint64_t headrestExPWMCount;
    bool headrestExPWMScale;
    uint64_t headrestExOpeningDuration;
    float processTemperatureStart;
    float processTemperatureEnd;
    uint64_t processPWMCount;
    bool processPWMScale;
    uint64_t processOpeningDuration100Percent;
    uint8_t processOpeningDurationEndPercent;
};

class Settings {
    Settings_struct settings;
public:
    Settings();

    void saveSettings();

    Settings_struct * getStruct();

};


#endif //MEGA_POWER_DRIVER_SETTINGS_H
