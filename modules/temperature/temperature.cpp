//
// Created by shewa on 16.10.19.
//

#include "temperature.h"
#include <list_utils.h>

#include <EventBus.h>

void Temperature::setup() {
    byte addr[8];
    byte rom[9];
    while (this->oneWire.search(addr)) {
        Thermometer data;
        memcpy(data.addr, addr, 8);

        this->oneWire.write(0x44); // Начинаем конверсию

        do {
            this->oneWire.write_bit(0); // Ждем пока не закончится.
        }while(!this->oneWire.read_bit());

        this->oneWire.write(0xBE); // Получаем температуру

        for(int i = 0; i < 9; i++){
            rom[i] = this->oneWire.read();
        }

        int16_t raw = (rom[1] << 8) | rom[0];
        byte cfg = (rom[4] & 0x60);
        // at lower res, the low bits are undefined, so let's zero them
        if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
        else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
        else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
        data.temperature = (float)raw / 16.;



        push_list_element(&this->thermometer_list, &data, sizeof(Thermometer));
    }
}

void Temperature::loop() {
    Thermometer *current = (Thermometer *) get_list_element(this->thermometer_list, this->current_thermometer);
    if(!this->conversionBegin){
        this->oneWire.reset();
        this->oneWire.select(current->addr);
        this->oneWire.write(0x44);
        this->conversionBegin = 1;
        return;
    } else{
        this->oneWire.write_bit(0);
        if(!this->oneWire.read_bit())
            return;
        this->oneWire.reset();
        this->oneWire.select(current->addr);
        this->oneWire.write(0xBE); // Получаем температуру
        uint8_t rom[12];
        for(int i = 0; i < 9; i++){
            rom[i] = this->oneWire.read();
        }

        int16_t raw = (rom[1] << 8) | rom[0];
        current->temperature = (float)raw / 16.;

        this->eventBus->generateEvent(TEMPERATURE_UPDATE_EVENT, current, sizeof(Thermometer));

        this->conversionBegin = 0;

        this->current_thermometer++;
        if(this->current_thermometer >= count_list(this->thermometer_list))
            this->current_thermometer = 0;
    }
}

Temperature::Temperature(uint8_t dataPin, EventBus *eventBus) :
        dataPin(dataPin),
        oneWire(dataPin),
        thermometer_list(NULL),
        current_thermometer(0),
        conversionBegin(0),
        eventBus(eventBus){
}

list_element *Temperature::getThermometerList() {
    return this->thermometer_list;
}
