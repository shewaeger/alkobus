#include "voltage.h"
#include "voltage_utils.hpp"

void VoltageControl::setup() {
    timer_setup();
}

void VoltageControl::loop() {
    reMathDimming();
    dimmingGlob = this->dimming;
}

void VoltageControl::setVoltage(float voltage) {
    this->currentVoltage = voltage;

    this->trueOutputVoltage = reMathVoltage(voltage);
}

void VoltageControl::reMathDimming() {
    float currentVoltage = (236. * analogRead(VOLTAGE_PIN)) / 883.;

    if (currentVoltage == 0)
        return;

    float percent = ((this->trueOutputVoltage* 100) / currentVoltage);
    this->dimming = (TIME_TO_DOWN / 100.) * percent;
}

float VoltageControl::reMathVoltage(double value) {
    if (value < 50)
        return value;

    return (value + 25.83)/1.48;
}

float VoltageControl::getCurrentVoltage() {
    return this->currentVoltage;
}

float VoltageControl::getOutputVoltage() {
    return this->outputVoltage;
}
