#include <Arduino.h>
#include "User_Setup.h"

int analogPin = 3;     // номер порта к которому подключен потенциометр
int val = 0;           // переменная для хранения считываемого значения

void setup()
{

    analogReference(INTERNAL1V1);
    Serial.begin(9600);
}

void loop()
{
    val = analogRead(analogPin);     // считываем значение
    Serial.println(val);
    Serial.println((1.1 / 1024.) * val);             // выводим полученное значение
}
