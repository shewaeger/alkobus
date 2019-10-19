//
// Created by shewa on 16.10.19.
//

#include "keyboard.h"

#define NOP 1

void Keyboard::setup() {
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
    }
    else if (lastKey == button) { // Если эта кнопка уже была нажата
        this->pushTime++;

        if (this->pushTime > LONG_PUSH_TIME + LONG_PUSH_EVENT_TIME) {
            Serial.print("long: ");
            Serial.println(button, HEX);
            NOP; // долгое нажатие клавиши. Генерируется раз в LONG_PUSH_EVENT_TIME тиков
            this->pushTime = LONG_PUSH_TIME; // защита от переполнения переменной
        }

    } else {
        lastKey = button;
        this->pushTime = 0;
        Serial.print("short: ");
        Serial.println(button, HEX);
        NOP;// Короткое нажатие клавиши (генерируется один раз)
    }

}

Keyboard::Keyboard(uint8_t ok, uint8_t left, uint8_t right, uint8_t down, uint8_t up) {
    this->buttonOkPin = ok;
    this->buttonLeftPin = left;
    this->buttonRightPin = right;
    this->buttonDownPin = down;
    this->buttonUpPin = up;
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
