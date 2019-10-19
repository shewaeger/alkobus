//
// Created by shewa on 16.10.19.
//

#ifndef MEGA_POWER_DRIVER_KEYBOARD_H
#define MEGA_POWER_DRIVER_KEYBOARD_H

#include <modules/Control.h>
#include <Arduino.h>

#define LONG_PUSH_TIME 2000
#define LONG_PUSH_EVENT_TIME 300

#define NO_BUTTONS 0
#define BUTTON_OK 1
#define BUTTON_LEFT 2
#define BUTTON_RIGHT 4
#define BUTTON_DOWN 8
#define BUTTON_UP 16

class Keyboard : public Control {
private:
    uint8_t buttonUpPin;
    uint8_t buttonDownPin;
    uint8_t buttonLeftPin;
    uint8_t buttonRightPin;
    uint8_t buttonOkPin;

    uint8_t lastKey = 0;

    uint32_t pushTime = 0;

    uint8_t getCurrentButton();
public:
    Keyboard() :
            buttonOkPin(22),
            buttonLeftPin(24),
            buttonRightPin(26),
            buttonDownPin(28),
            buttonUpPin(30) {}

            Keyboard(uint8_t ok, uint8_t left, uint8_t right, uint8_t down, uint8_t up);

    void setup();

    void loop();
};


#endif //MEGA_POWER_DRIVER_KEYBOARD_H
