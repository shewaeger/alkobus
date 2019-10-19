#include <Arduino.h>
#include "User_Setup.h"
#include <ModManager.h>

void setup() {
    Serial.begin(9600);
    Serial.println("Starting....");
    ModManager *manager = ModManager::getManager();
    manager->setup();
    Serial.println("Started.");
}

void loop() {
    ModManager *manager = ModManager::getManager();
    manager->loop();
    EventBus *bus = manager->getEventBus();
    Event *event;
    while ((event = bus->getLastEvent()) != NULL) {
        Serial.println("Event receive");
        switch (event->type) {
            case TEMPERATURE_UPDATE_EVENT: {
                Serial.println("TYPE: temperature_update_event");
                Thermometer *thermometer = (Thermometer *) event->data;
                Serial.print("ADDRESS: ");
                for (int i = 0; i < 8; i++) {
                    if (thermometer->addr[i] < 0x10)
                        Serial.print("0");
                    Serial.print(thermometer->addr[i], HEX);
                }
                Serial.println();
                Serial.print("TEMPERATURE: ");
                Serial.println(thermometer->temperature);
                break;
            }
            case LONG_PUSH_KEY_EVENT: {
                Serial.println("TYPE: long_push_key_event");
                uint8_t key = *(uint8_t *) event->data;
                Serial.print("KEY: ");
                switch (key) {
                    case BUTTON_OK:
                        Serial.println("BUTTON_OK");
                        break;
                    case BUTTON_UP:
                        Serial.println("BUTTON_UP");
                        break;
                    case BUTTON_DOWN:
                        Serial.println("BUTTON_DOWN");
                        break;
                    case BUTTON_RIGHT:
                        Serial.println("BUTTON_RIGHT");
                        break;
                    case BUTTON_LEFT:
                        Serial.println("BUTTON_LEFT");
                        break;
                }
                break;
            }
            case SHORT_PUSH_KEY_EVENT: {
                Serial.println("TYPE: short_push_key_event");
                uint8_t key = *(uint8_t *) event->data;
                Serial.print("KEY: ");
                switch (key) {
                    case BUTTON_OK:
                        Serial.println("BUTTON_OK");
                        break;
                    case BUTTON_UP:
                        Serial.println("BUTTON_UP");
                        break;
                    case BUTTON_DOWN:
                        Serial.println("BUTTON_DOWN");
                        break;
                    case BUTTON_RIGHT:
                        Serial.println("BUTTON_RIGHT");
                        break;
                    case BUTTON_LEFT:
                        Serial.println("BUTTON_LEFT");
                        break;
                }
                break;
            }
        }
        bus->removeEvent(event);
    }
}