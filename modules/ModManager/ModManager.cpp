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
#include <Valve.h>
#include <Settings.h>
#include <TenSwitch.h>
#include <Speaker.h>

ModManager *ModManager::manager = NULL;
byte customChar[] = {
        B00000,
        B01111,
        B00011,
        B00101,
        B01001,
        B10000,
        B00000,
        B00000
};
byte exitChar[] = {
        B00000,
        B11111,
        B11001,
        B11101,
        B11101,
        B11111,
        B01100,
        B00100
};
ModManager *ModManager::getManager() {
    if (manager == NULL)
        manager = new ModManager();
    return manager;
}

ModManager::ModManager() {
    this->eventBus = new EventBus();
    this->temperature = new Temperature(10, this->eventBus);
    this->voltageControl = new VoltageControl();
    this->keyboard = new Keyboard(31, 29, 27, 25, 23, this->eventBus);
    this->lcd = new LiquidCrystal_I2C(0x3f, 16, 2);
//    this->lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    this->valve = new Valve(51);
    this->settings = new Settings();
    this->tenSwitch = new TenSwitch();
    this->speaker = new Speaker();
}

void ModManager::setup() {
    this->temperature->setup();
    Serial.println("Temperature started");
    this->voltageControl->setup();
    Serial.println("VoltageControl started");
    this->keyboard->setup();
    Serial.println("Keyboard started");
    this->tenSwitch->setup();
    this->speaker->setup();
    this->lcd->init();
    this->lcd->backlight();
    this->lcd->clear();
    this->lcd->createChar(0, customChar);
    this->lcd->createChar(1, exitChar);
    this->lcd->setCursor(0,0);
    Serial.println("LCD started");
}

void ModManager::loop() {
    this->temperature->loop();
    this->voltageControl->loop();
    this->keyboard->loop();
    this->valve->loop();
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

Valve *ModManager::getValve() {
    return this->valve;
}

Settings *ModManager::getSettings() {
    return this->settings;
}

TenSwitch *ModManager::getTenSwitch() {
    return this->tenSwitch;
}

Speaker *ModManager::getSpeaker() {
    return this->speaker;
}
