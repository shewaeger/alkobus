//
// Created by shewa on 16.10.19.
//

#ifndef MEGA_POWER_DRIVER_TEMPERATURE_H
#define MEGA_POWER_DRIVER_TEMPERATURE_H


#include <modules/Control.h>
#include <OneWire.h>
struct list_element;
class Temperature : public Control{
private:
    OneWire oneWire;
    uint8_t dataPin;
    list_element *thermometer_list;
    int current_thermometer;
    uint8_t conversionBegin;
public:
    Temperature(uint8_t dataPin);
    void setup();
    void loop();
};


#endif //MEGA_POWER_DRIVER_TEMPERATURE_H
