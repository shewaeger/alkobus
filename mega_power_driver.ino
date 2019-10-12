#include <Arduino.h>
#include "User_Setup.h"

#define TIME_TO_DOWN 0x4AE0

#define TIME_10_uS 0x0015

#define START_TIMER (TCCR1B = (1 << CS11))
#define STOP_TIMER (TCCR1B = 0)

#define POWER_PIN 36

uint16_t dimming = 0;

void null_up() {
    OCR1A = TIME_TO_DOWN - dimming;
    OCR1B = OCR1A + TIME_10_uS;
    TCNT1 = 0;
    START_TIMER;
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

    TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);

    pinMode(POWER_PIN, OUTPUT);
    attachInterrupt(INT2, null_up, RISING);
    Serial.begin(9600);

    sei();
}

void loop() {
    int available = Serial.available();
    char input[80];
    if (!available)
        return;

    size_t reading = Serial.readBytesUntil('\n', input, 79);
    input[reading] = 0;

    long value = strtol(input, NULL, 10);
    if(value < 0)
        value = 0;
    if(value > 96)
        value = 96;
    dimming = (TIME_TO_DOWN / 100) * value;
}
