//
// Created by shewa on 19.10.19.
//

#include <stddef.h>
#include <EventBus.h>
#include <temperature.h>
#include <voltage.h>
#include <Keyboard.h>
#include <LiquidCrystal_I2C.h>
#include "ModManager.h"

ModManager *ModManager::manager = NULL;

ModManager *ModManager::getManager() {
    if (manager == NULL)
        manager = new ModManager();
    return manager;
}

ModManager::ModManager() {
    this->eventBus = new EventBus();
    this->temperature = new Temperature(39, this->eventBus);
    this->voltageControl = new VoltageControl();
    this->keyboard = new Keyboard(31, 29, 27, 25, 23, this->eventBus);
    this->lcd = new LiquidCrystal_I2C(0x3f, 16, 2);
}

void ModManager::setup() {
    this->temperature->setup();
    this->voltageControl->setup();
    this->keyboard->setup();
    this->lcd->init();
    this->lcd->backlight();
    this->lcd->clear();
    this->lcd->setCursor(0,0);
}

void ModManager::loop() {
    this->temperature->loop();
    this->voltageControl->loop();
    this->keyboard->loop();
}

EventBus *ModManager::getEventBus() {
    return this->eventBus;
}

LiquidCrystal_I2C *ModManager::getLCD() {
    return lcd;
}

Temperature *ModManager::getThermometers() {
    return this->temperature;
}

VoltageControl *ModManager::getVoltageControl() {
    return this->voltageControl;
}
