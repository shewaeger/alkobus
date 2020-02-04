//
// Created by shewa on 31.12.19.
//

#include <Arduino.h>
#include "Valve.h"



void Valve::close() {
    digitalWrite(pin, !mode);
}

void Valve::open() {
    digitalWrite(pin, mode);
}

Valve::Valve(int pin, bool mode) {
    this->pwmStatus = false;
    this->pin = pin;
    this->mode = mode;
    pinMode(this->pin, OUTPUT);
    this->close();

}

Valve::~Valve() {

}

void Valve::setPWM(uint64_t pwmCount, bool pwmScale) {
    this->pwmCount = pwmCount;
    this->pwmScale = pwmScale;
    if(!pwmScale)
        this->pwm = 60000 / pwmCount;
    else
        this->pwm = 3600000 / pwmCount;
}

void Valve::setOpeningDuration(uint64_t duration) {
    if(pwm < duration)
        duration = pwm;
    this->openingDuration = duration;
}

void Valve::loop() {
    if(!pwmStatus)
        return;
    if(this->pwm == 0 || this->openingDuration == 0) {
        this->close();
        return;
    }
    if(this->openingDuration == this->pwm){
        this->open();
        return;
    }
    uint64_t millis_t = millis();
    if(millis_t - lastPWM >= openingDuration)
        this->close();

    if(millis_t - lastPWM  >= pwm){
        this->open();
        this->lastPWM = millis_t;
    }
}

uint64_t Valve::getOpeningDuration() {
    return this->openingDuration;
}

uint64_t Valve::getPWMScale() {
    return this->pwmScale;
}

uint64_t Valve::getPWMCount() {
    return this->pwmCount;
}

bool Valve::switchPWMStatus() {
    this->pwmStatus = !this->pwmStatus;
    return this->pwmStatus;
}

void Valve::setPWMStatus(bool status) {
    this->pwmStatus = status;
}


