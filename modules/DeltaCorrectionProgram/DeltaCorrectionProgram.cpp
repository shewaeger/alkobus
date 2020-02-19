//
// Created by shewa on 15.02.2020.
//

#include <ModManager.h>
#include "DeltaCorrectionProgram.h"
#include <temperature.h>
#include <Settings.h>
#include <LiquidCrystal_I2C.h>
#include <EventBus.h>
#include <Keyboard.h>

void DeltaCorrectionProgram::setup() {
    Serial.println("DeltaCorrectionProgram");
    Settings_struct *settings = ModManager::getManager()->getSettings()->getStruct();
    thermometer1 = ModManager::getManager()->getThermometers()->getThermometer(settings->thermometer1Addr);
    thermometer2 = ModManager::getManager()->getThermometers()->getThermometer(settings->thermometer2Addr);
    this->isExit = false;
}

void DeltaCorrectionProgram::loop() {
    Serial.println("test");
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    if(thermometer1 == NULL || thermometer2 == NULL){
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
    Settings_struct *settings = ModManager::getManager()->getSettings()->getStruct();
    float delta = fabs(thermometer1->temperature - thermometer2->temperature);
    if(delta <= settings->allowedDelta || isExit){
        exit(0);
    }
    char t1Str[6];
    char t2Str[6];
    char deltaStr[6];
    char buffer[32] = "";
//    Serial.println(thermometer1->temperature);
//    Serial.println(thermometer2->temperature);
    dtostrf(thermometer1->temperature, 3, 2, t1Str);
    dtostrf(thermometer2->temperature, 3, 2, t2Str);
    dtostrf(delta, 3, 2, deltaStr);
    sprintf(buffer, "T1:%s T2:%s      ", t1Str, t2Str);
    lcd->setCursor(0, 0);
    lcd->print(buffer);
    sprintf(buffer, "D:%s ", deltaStr);
    lcd->setCursor(0, 1);
    lcd->print(buffer);
    lcd->print((char)0x7e);
    lcd->print((char)0x01);
    lcd->print("Exit");
}

void DeltaCorrectionProgram::event(Event *event) {
    if(event->type == SHORT_PUSH_KEY_EVENT && (*(uint8_t *) event->data) == BUTTON_OK){
        isExit = true;
    }
}

char *DeltaCorrectionProgram::getName() {
    return "";
}
