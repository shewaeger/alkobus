//
// Created by shewa on 13.02.2020.
//

#include <Arduino.h>
#include <ModManager.h>
#include "PrimarySelectionProgram.h"
#include <Valve.h>
#include <LiquidCrystal_I2C.h>
#include <EventBus.h>
#include <Keyboard.h>
#include <voltage.h>
#include <Settings.h>

void PrimarySelectionProgram::setup() {
    this->processStarting = millis();
    Valve *valve = ModManager::getManager()->getValve();
    valve->setPWM(*pwmCount, *pwmScale);
    valve->setOpeningDuration(*openingDuration);
    Settings_struct *settings = ModManager::getManager()->getSettings()->getStruct();
    ModManager::getManager()->getVoltageControl()->setVoltage(settings->workingVoltage);
    isExit = false;
}

void PrimarySelectionProgram::loop() {
    Valve * valve = ModManager::getManager()->getValve();
    if(millis() - this->processStarting >= *processTime || isExit) {
        valve->disablePWM();
        valve->close();
        exit(0);
        return;
    }
    valve->enablePWM();
    drawScreen();
}

void PrimarySelectionProgram::event(Event *event) {
    if(event->type == SHORT_PUSH_KEY_EVENT && (*(uint8_t *) event->data) == BUTTON_OK){
        isExit = true;
    }
}

char *PrimarySelectionProgram::getName() {
    return "";
}

PrimarySelectionProgram::PrimarySelectionProgram(unsigned long *processTime, unsigned long *pwmCount, bool *pwmScale,
                                                 unsigned long *openingDuration) : processTime(processTime),
                                                                                   pwmCount(pwmCount),
                                                                                   pwmScale(pwmScale),
                                                                                   openingDuration(openingDuration) {}

void PrimarySelectionProgram::generateLeftTime() {
    unsigned long leftTime = (*processTime) - (millis() - processStarting);
    unsigned long hour = leftTime / 3600000;
    unsigned long mod = leftTime % 3600000;
    unsigned long minutes = mod / 60000;
    mod %= 60000;
    unsigned long seconds = mod / 1000;
    sprintf(timeShowBuffer, "Left: %02d:", hour);
    sprintf(timeShowBuffer + strlen(timeShowBuffer), "%02d:", minutes);
    sprintf(timeShowBuffer + strlen(timeShowBuffer), "%02d          ", seconds);
}

void PrimarySelectionProgram::drawScreen() {
    generateLeftTime();
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    lcd->setCursor(0, 0);
    lcd->print(timeShowBuffer);
    lcd->setCursor(0, 1);
    lcd->print((char)0x7e);
    lcd->print(' ');
    lcd->print((char)0x1);
    lcd->print("EXIT                ");
}
