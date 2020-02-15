//
// Created by shewa on 25.10.19.
//

#include <EventBus.h>
#include <Keyboard.h>
#include "VoltageProgram.h"
#include "ModManager.h"
#include <LiquidCrystal_I2C.h>
#include "voltage.h"
#include <Valve.h>

void VoltageProgram::backgroundLoop() {
    Program::backgroundLoop();
}

void VoltageProgram::setup() {
    this->voltage = 0;
    this->voltageCounter = 0;
    this->currentLine = 0;
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    lcd->clear();
    lcd->setCursor(1, 0);
    lcd->print("V:");
    lcd->setCursor(1, 1);
    lcd->print("EXIT");
    lcd->setCursor(6, 1);
    lcd->print("Vc:");
}

void VoltageProgram::loop() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    VoltageControl *voltage = ModManager::getManager()->getVoltageControl();
    char voltageOut[7];
    lcd->setCursor(0, !currentLine);
    lcd->print(" ");
    lcd->setCursor(0, currentLine);
    lcd->print((char)0x7e);

    dtostrf(this->voltage, 5, 1, voltageOut);

    lcd->setCursor(6, 0);
    lcd->print(voltageOut);
    lcd->print("0.5");
    if(!(voltageCounter % 64)) {
        lcd->setCursor(9, 1);
        lcd->print("0.00");
        lcd->print(voltage->getInputVoltage());
    }
    voltageCounter++;
}

void VoltageProgram::event(Event *event) {
    if(event->type != LONG_PUSH_KEY_EVENT && event->type != SHORT_PUSH_KEY_EVENT)
        return;

    uint8_t code = *(uint8_t *)event->data;
    if(code == BUTTON_UP || code == BUTTON_DOWN){
        if((code == BUTTON_DOWN && currentLine) || (code == BUTTON_UP && !currentLine) )
            return;
        currentLine += (code == BUTTON_UP) ? -1 : +1;
    }

    if(currentLine && code == BUTTON_OK) {
        this->exit(0);
    }

    if(code == BUTTON_RIGHT || code == BUTTON_LEFT){
        VoltageControl *vc = ModManager::getManager()->getVoltageControl();
        vc->setVoltage( voltage + ((BUTTON_LEFT == code) ? -1 : +1 ));
        this->voltage = vc->getCurrentVoltage();
    }

}

char *VoltageProgram::getName() {
    return this->name;
}

VoltageProgram::VoltageProgram(char *name) {
    this->name = name;
}
