//
// Created by shewa on 16.10.19.
//

#ifndef MEGA_POWER_DRIVER_TEMPERATURE_H
#define MEGA_POWER_DRIVER_TEMPERATURE_H


#include <OneWire.h>

struct Thermometer {
    uint8_t addr[8];
    float temperature;
};

class EventBus;

struct list_element;
class Temperature {
private:
    OneWire oneWire;
    uint8_t dataPin;
    list_element *thermometer_list;
    int current_thermometer;
    uint8_t conversionBegin;
    EventBus *eventBus;
public:
    Temperature(uint8_t dataPin, EventBus *eventBus);
    list_element *getThermometerList();
    void setup();
    void loop();
};


#endif //MEGA_POWER_DRIVER_TEMPERATURE_H
