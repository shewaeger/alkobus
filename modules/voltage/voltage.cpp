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

    if(voltage < 0)
        voltage = 0;
    if(voltage > 190)
        voltage = 190;

    this->currentVoltage = voltage;

    this->trueOutputVoltage = reMathVoltage(voltage);
}

void VoltageControl::reMathDimming() {
    float currentVoltage = getInputVoltage();

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

float VoltageControl::getInputVoltage(){
   return (236. * analogRead(VOLTAGE_PIN)) / 883.;
}
