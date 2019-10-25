//
// Created by shewa on 25.10.19.
//

#include <EventBus.h>
#include <Keyboard.h>
#include "TemperatureProgram.h"
#include "ModManager.h"
#include "LiquidCrystal_I2C.h"
#include "voltage.h"

void TemperatureProgram::backgroundLoop() {
    Program::backgroundLoop();
}

void TemperatureProgram::setup() {
    this->voltage = 0;
    this->voltageCounter = 0;
    this->currentLine = 0;
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();

    lcd->setCursor(1, 0);
    lcd->print("V:");
    lcd->setCursor(1, 1);
    lcd->print("EXIT");
    lcd->setCursor(6, 1);
    lcd->print("Vc:");
}

void TemperatureProgram::loop() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    VoltageControl *voltage = ModManager::getManager()->getVoltageControl();

    lcd->setCursor(0, !currentLine);
    lcd->print(" ");
    lcd->setCursor(0, currentLine);
    lcd->print((char)0x7e);

    lcd->setCursor(6, 0);
    lcd->print(this->voltage);

    if(!(voltageCounter % 64)) {
        lcd->setCursor(9, 1);
        lcd->print(voltage->getInputVoltage());
    }
    voltageCounter++;
}

void TemperatureProgram::event(Event *event) {
    if(event->type != LONG_PUSH_KEY_EVENT && event->type != SHORT_PUSH_KEY_EVENT)
        return;

    uint8_t code = *(uint8_t *)event->data;
    if(code == BUTTON_UP || code == BUTTON_DOWN){
        if((code == BUTTON_DOWN && currentLine) || (code == BUTTON_UP && !currentLine) )
            return;
        currentLine += (code == BUTTON_UP) ? -1 : +1;
    }

    if(currentLine && code == BUTTON_OK)
        this->exit();

    if(code == BUTTON_RIGHT || code == BUTTON_LEFT){
        VoltageControl *vc = ModManager::getManager()->getVoltageControl();
        vc->setVoltage( voltage + ((BUTTON_LEFT == code) ? -1 : +1 ));
        this->voltage = vc->getCurrentVoltage();
    }

}
