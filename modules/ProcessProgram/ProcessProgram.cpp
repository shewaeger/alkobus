//
// Created by shewa on 15.02.2020.
//

#include <Settings.h>
#include <ModManager.h>
#include <Valve.h>
#include <voltage.h>
#include <temperature.h>
#include "ProcessProgram.h"
#include <LiquidCrystal_I2C.h>
void ProcessProgram::setup() {
    this->firstStep = true;
    this->isWrongDelta = false;
    Settings_struct *settings = ModManager::getManager()->getSettings()->getStruct();
    ModManager::getManager()->getVoltageControl()->setVoltage(settings->workingVoltage);
    thermometer1 = ModManager::getManager()->getThermometers()->getThermometer(settings->thermometer1Addr);
    thermometer2 = ModManager::getManager()->getThermometers()->getThermometer(settings->thermometer2Addr);
    odEnd = (settings->processOpeningDuration100Percent / 100) * settings->processEndPercent;
    timeStart = millis();
}

void ProcessProgram::loop() {
    Settings_struct *settings = ModManager::getManager()->getSettings()->getStruct();
    Valve *valve = ModManager::getManager()->getValve();
    if(!isWrongDelta && fabs(thermometer1->temperature - thermometer2->temperature) > settings->allowedDelta){
        Serial.println("Delta is wrong");
        isWrongDelta = true;
    }
    if(isWrongDelta){
        valve->disablePWM();
        if(!firstStep && fabs(thermometer1->temperature - thermometer2->temperature) <= settings->allowedDelta){
            pts = thermometer1->temperature;
            calculateCoefficients();
        }
        isWrongDelta = false;
        Serial.println("Delta is allowed");
    }
    if(thermometer1->temperature >= settings->processTemperatureEnd){
        exit(0);
    }

    if(firstStep && !isWrongDelta){
        if(thermometer1->temperature > settings->processTemperatureStart) {
            firstStep = false;
        }
        valve->enablePWM();
        valve->setPWM(settings->processPWMCount, settings->processPWMScale);
        valve->setOpeningDuration(settings->processOpeningDuration100Percent);
    } else if(!firstStep && !isWrongDelta){
        valve->enablePWM();
        unsigned long currentOD = (unsigned long)(k*thermometer1->temperature + b);
        valve->setOpeningDuration(currentOD);
    }
    drawScreen();
}

void ProcessProgram::event(Event *event) {
    Program::event(event);
}

char *ProcessProgram::getName() {
    return "";
}

void ProcessProgram::drawScreen() {
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    char buffer[32];
    char temp1Buffer[6];
    char temp2Buffer[6];

    dtostrf(thermometer1->temperature, 2, 1, temp1Buffer);
    dtostrf(thermometer2->temperature, 2, 1, temp2Buffer);
    sprintf(buffer, "T1:%s T2:%s   ", temp1Buffer, temp2Buffer);
    lcd->setCursor(0,0);
    lcd->print(buffer);

    dtostrf(fabs(thermometer1->temperature - thermometer2->temperature), 2, 1, temp1Buffer);
    sprintf(buffer, "D:%s t:", temp1Buffer);
    unsigned long leftTime =  millis() - timeStart;
    unsigned long hour = leftTime / 3600000;
    unsigned long mod = leftTime % 3600000;
    unsigned long minutes = mod / 60000;
    mod %= 60000;
    unsigned long seconds = mod / 1000;
    sprintf(buffer + strlen(buffer), "%02d:", hour);
    sprintf(buffer + strlen(buffer), "%02d:", minutes);
    sprintf(buffer + strlen(buffer), "%02d  ", seconds);
    lcd->setCursor(0, 1);
    lcd->print(buffer);
}

void ProcessProgram::calculateCoefficients() {
    this->k = (odEnd - od100) / (pte - pts);
    this->b = k * pts;
}
