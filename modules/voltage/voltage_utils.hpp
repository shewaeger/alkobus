#include <Arduino.h>

/*
 * Подключаем обработку прерываний
 */
// Около 10мс
#define TIME_TO_DOWN 0x4AE0

// Пин для подключения датчика нуля. Использовать только ножки для прерываний (INT0 - INT5)
#define NULL_PIN 2
#define TIME_10_uS 0x0015

#define START_TIMER_256 (TCCR1B = (1 << CS11)) // Таймер работает в clk / 8
#define STOP_TIMER (TCCR1B = 0)

// Пин для подключения вывода, который управляет диммированием.
#define POWER_PIN 4
// Пин для измерения входного напряжения
#define VOLTAGE_PIN 3
uint16_t dimmingGlob;
void null_up() {
    OCR1A = TIME_TO_DOWN - dimmingGlob;
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

void timer_setup(){
    cli(); // отключить глобальные прерывания

    TCCR1A = 0;
    TCCR1B = 0;

    // Разрешаем прерывания таймера по совпадению с OCR1A и OCR1B
    TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);

    pinMode(POWER_PIN, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(NULL_PIN), null_up, RISING);

    // Для точности расчета входного напряжения используем внутреннее опорное напряжение в 1.1В
    analogReference(INTERNAL1V1);

    sei();
}

