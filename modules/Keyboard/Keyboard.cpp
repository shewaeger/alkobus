//
// Created by shewa on 16.10.19.
//

#include <EventBus.h>
#include "Keyboard.h"



void Keyboard::setup() {
    pinMode(this->buttonUpPin, INPUT);
    pinMode(this->buttonLeftPin, INPUT);
    pinMode(this->buttonRightPin, INPUT);
    pinMode(this->buttonDownPin, INPUT);
    pinMode(this->buttonOkPin, INPUT);
    digitalWrite(this->buttonOkPin, HIGH);
    digitalWrite(this->buttonLeftPin, HIGH);
    digitalWrite(this->buttonRightPin, HIGH);
    digitalWrite(this->buttonDownPin, HIGH);
    digitalWrite(this->buttonUpPin, HIGH);
}

void Keyboard::loop() {
    uint8_t button = getCurrentButton();
    if (button == NO_BUTTONS) {
        this->lastKey = NO_BUTTONS;
        this->pushTime = 0;
        shortKeyEvent = 1;
    }
    else if (lastKey == button) { // Если эта кнопка уже была нажата
        this->pushTime++;
        if (this->pushTime > LONG_PUSH_TIME + LONG_PUSH_EVENT_TIME) {
            this->pushTime = LONG_PUSH_TIME; // защита от переполнения переменной
            this->generateEvent(LONG_PUSH_KEY_EVENT);
        } else if(this->pushTime > SHORT_PUSH_TIME && shortKeyEvent){
            this->generateEvent(SHORT_PUSH_KEY_EVENT);
            shortKeyEvent = 0;
        }
    } else {
        lastKey = button;
        this->pushTime = 0;
    }

}

Keyboard::Keyboard(uint8_t ok, uint8_t left, uint8_t right, uint8_t down, uint8_t up, EventBus * eventBus) {
    this->buttonOkPin = ok;
    this->buttonLeftPin = left;
    this->buttonRightPin = right;
    this->buttonDownPin = down;
    this->buttonUpPin = up;
    this->eventBus = eventBus;
}

uint8_t Keyboard::getCurrentButton() {
    if (!digitalRead(this->buttonOkPin))
        return BUTTON_OK;
    if (!digitalRead(this->buttonLeftPin))
        return BUTTON_LEFT;
    if (!digitalRead(this->buttonRightPin))
        return BUTTON_RIGHT;
    if (!digitalRead(this->buttonDownPin))
        return BUTTON_DOWN;
    if (!digitalRead(this->buttonUpPin))
        return BUTTON_UP;
    return NO_BUTTONS;
}

void Keyboard::generateEvent(uint8_t type) {
    this->eventBus->generateEvent(type, &this->lastKey, sizeof(this->lastKey));
}
