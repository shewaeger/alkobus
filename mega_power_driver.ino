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
                Thermometer *thermometer = (Thermometer *) event->data;
                for (int i = 0; i < 8; i++) {
                    if (thermometer->addr[i] < 0x10)
                        Serial.print("0");
                    Serial.print(thermometer->addr[i], HEX);
                }
                list_element *list = manager->getThermometers()->getThermometerList();
                size_t count = count_list(list);
                manager->getLCD()->clear();
                char Tstr[10];
                for (int i = 0; i < count; i++) {
                    Thermometer *t = (Thermometer *) get_list_element(list, i);
                    manager->getLCD()->setCursor((i % 2) * 8, i >= 2);
                    manager->getLCD()->print("T:");
                    dtostrf(t->temperature, 5, 1, Tstr);
                    manager->getLCD()->print(Tstr);
                }
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