#include <Arduino.h>
#include "User_Setup.h"

#define BTN_OK 22
#define BTN_LEFT 24
#define BTN_RIGHT 26
#define BTN_UP 30
#define BTN_DOWN 28

#include <LiquidCrystal_I2C.cpp>

LiquidCrystal_I2C lc(0x3f, 16, 2);

void setup(){
    Serial.begin(9600);

    // Configure buttons
    digitalWrite(BTN_OK, HIGH);
    digitalWrite(BTN_DOWN, HIGH);
    digitalWrite(BTN_LEFT, HIGH);
    digitalWrite(BTN_RIGHT, HIGH);
    digitalWrite(BTN_UP, HIGH);

    lc.init();
    lc.backlight();
    lc.setCursor(0, 0);
    lc.print("U ");
}

uint8_t up = 0;
void loop(){
}