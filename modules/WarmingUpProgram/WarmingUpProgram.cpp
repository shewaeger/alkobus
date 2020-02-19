//
// Created by shewa on 13.02.2020.
//

#include <ModManager.h>
#include "WarmingUpProgram.h"
#include <voltage.h>
#include <TenSwitch.h>
#include <temperature.h>
#include <Settings.h>
#include <LiquidCrystal_I2C.h>
#include <EventBus.h>
#include <Keyboard.h>

void WarmingUpProgram::setup() {
    Settings_struct * settings = ModManager::getManager()->getSettings()->getStruct();
    thermometer = ModManager::getManager()->getThermometers()->getThermometer(settings->thermometer1Addr);
    processStarting = millis();
    this->isExit = false;
}

void WarmingUpProgram::loop() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    Settings_struct *settings = ModManager::getManager()->getSettings()->getStruct();
    if(thermometer == NULL){
        if(isExit){
            exit(1);
            return;
        }
        lcd->setCursor(0, 0);
        lcd->print("Unable to find  ");
        lcd->setCursor(0, 1);
        lcd->print("thermometers    ");
        return;
    }
    if(thermometer->temperature >= settings->initialTemperature || isExit){
        Serial.println("HEATED UP");
        ModManager::getManager()->getVoltageControl()->setVoltage(settings->workingVoltage);
        ModManager::getManager()->getTenSwitch()->disable();
        exit(0);
        return;
    }
    ModManager::getManager()->getVoltageControl()->setVoltage(190);
    ModManager::getManager()->getTenSwitch()->enable();

    char buffer[32];
    char numBuf[10];
    dtostrf(thermometer->temperature, 1, 2, numBuf);
    sprintf(buffer, "t:%s\xDF        ", numBuf);
    lcd->setCursor(0,0);
    lcd->print(buffer);
    buffer[0] = 0;
    unsigned long leftTime =  millis() - processStarting;
    unsigned long hour = leftTime / 3600000;
    unsigned long mod = leftTime % 3600000;
    unsigned long minutes = mod / 60000;
    mod %= 60000;
    unsigned long seconds = mod / 1000;
    sprintf(buffer, "%02d:", hour);
    sprintf(buffer + strlen(buffer), "%02d:", minutes);
    sprintf(buffer + strlen(buffer), "%02d  ", seconds);
    lcd->setCursor(0, 1);
    lcd->print(buffer);
    lcd->print((char)0x7e);
    lcd->print((char)0x1);
    lcd->print("Exit");


}

void WarmingUpProgram::event(Event *event) {
    if(event->type == SHORT_PUSH_KEY_EVENT && (*(uint8_t *) event->data) == BUTTON_OK){
        isExit = true;
    }
}

char *WarmingUpProgram::getName() {
    return "";
}
