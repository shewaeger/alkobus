#include <Arduino.h>
#include "User_Setup.h"

#define TIME_TO_DOWN 0x4AE0
#define NULL_PIN 2
#define TIME_10_uS 0x0015

#define START_TIMER_256 (TCCR1B = (1 << CS11)) // Таймер работает в clk / 256
#define STOP_TIMER (TCCR1B = 0)

#define POWER_PIN 36
#define MAX_INPUT_SIZE 80

#define VOLTAGE_PIN 3

uint16_t dimming = 0;
double outVoltage = 0;
char input[MAX_INPUT_SIZE];


void null_up() {
    OCR1A = TIME_TO_DOWN - dimming;
    OCR1B = OCR1A + TIME_10_uS;
    TCNT1 = 0;
    START_TIMER_256;
}

ISR(TIMER1_COMPA_vect) {
    digitalWrite(POWER_PIN, 1);
}

ISR(TIMER1_COMPB_vect) {
    digitalWrite(POWER_PIN, 0);
    STOP_TIMER;
}

void setup() {


    cli(); // отключить глобальные прерывания

    TCCR1A = 0;
    TCCR1B = 0;

    // Разрешаем прерывания таймера по совпадению с OCR1A и OCR1B
    TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);

    pinMode(POWER_PIN, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(NULL_PIN), null_up, RISING);

    // Для точности расчета входного напряжения используем внутреннее опорное напряжение в 1.1В
    analogReference(INTERNAL1V1);

    Serial.begin(9600);

    sei();
}

void mathDimming() {
    float currentVoltage = (236. * analogRead(VOLTAGE_PIN)) / 885.;

    if (currentVoltage == 0)
        return;

    float percent = ((outVoltage * 100) / currentVoltage);
    dimming = (TIME_TO_DOWN / 100.) * percent;
}

double reMathVoltage(double value) {
    if (value < 50)
        return value;

    return (value + 25.83)/1.45;
}

void loop() {
    mathDimming();

    // Чтение значения с последовательного порта
    int available = Serial.available();
    if (!available)
        return;

    size_t reading = Serial.readBytesUntil('\n', input, MAX_INPUT_SIZE - 1);
    input[reading] = 0;

    double tmpVal = strtod(input, NULL);

    if (tmpVal < 0)
        tmpVal = 0;
    if (tmpVal > 190)
        tmpVal = 190;

    outVoltage = reMathVoltage(tmpVal);
}
