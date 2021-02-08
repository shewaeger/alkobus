//
// Created by shewa on 26.10.19.
//

#include "TemperatureProgram.h"
#include <ModManager.h>
#include <temperature.h>
#include <LiquidCrystal_I2C.h>
TemperatureProgram::~TemperatureProgram() {

}

void TemperatureProgram::backgroundLoop() {
}

void TemperatureProgram::setup() {
    Temperature * temperature = ModManager::getManager()->getThermometers();
    ModManager::getManager()->getLCD()->clear();
    this->thermometers = temperature->getThermometerList();
}

void TemperatureProgram::loop() {
    LiquidCrystal_I2C * lcd = ModManager::getManager()->getLCD();

}

void TemperatureProgram::event(Event *event) {

}
