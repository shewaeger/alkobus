#include <Arduino.h>
#include "User_Setup.h"
#include "voltage.h"
#include "keyboard.h"
#include "temperature.h"

VoltageControl voltageControl;
Keyboard keyboard;
Temperature temperature(10);
void setup(){
    keyboard.setup();
    voltageControl.setup();
    Serial.begin(9600);
    temperature.setup();
    Serial.println("Updated");
}


int voltage = 0;
uint8_t up = 1;
int counter = 0;
void loop(){
    voltageControl.loop();
    if(up) {
        counter++;
        if(counter > 100) {
            counter = 0;
            voltage++;
            up = voltage < 190;
        }
    }
    else{
        counter++;
        if(counter > 100) {
            counter = 0;
            voltage--;
            up = voltage < 0;
        }
    }
    voltageControl.setVoltage(voltage);

    keyboard.loop();

    temperature.loop();
}