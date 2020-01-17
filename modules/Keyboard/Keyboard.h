//
// Created by shewa on 16.10.19.
//

#ifndef MEGA_POWER_DRIVER_KEYBOARD_H
#define MEGA_POWER_DRIVER_KEYBOARD_H

#include <Arduino.h>

#define LONG_PUSH_TIME 40
#define LONG_PUSH_EVENT_TIME 5

#define NO_BUTTONS 0
#define BUTTON_OK 1
#define BUTTON_LEFT 2
#define BUTTON_RIGHT 4
#define BUTTON_DOWN 8
#define BUTTON_UP 16

class EventBus;

class Keyboard {
private:
    uint8_t buttonUpPin;
    uint8_t buttonDownPin;
    uint8_t buttonLeftPin;
    uint8_t buttonRightPin;
    uint8_t buttonOkPin;

    uint8_t lastKey = 0;

    uint32_t pushTime = 0;

    EventBus * eventBus;

    uint8_t getCurrentButton();
    void generateEvent(uint8_t type);
public:
    Keyboard() :
            buttonOkPin(23),
            buttonLeftPin(25),
            buttonRightPin(27),
            buttonDownPin(29),
            buttonUpPin(31) {}

            Keyboard(uint8_t ok, uint8_t left, uint8_t right, uint8_t down, uint8_t up, EventBus *eventBus);

    void setup();

    void loop();
};


#endif //MEGA_POWER_DRIVER_KEYBOARD_H
