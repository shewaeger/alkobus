
#include <modules/Control.h>
#include <Arduino.h>
class VoltageControl: public Control{

private:
    float currentVoltage;
    float outputVoltage;
    float trueOutputVoltage;
    uint16_t dimming;

    void reMathDimming();

    static float reMathVoltage(double value);

public:
    void setup();
    void loop();

    void setVoltage(float voltage);
    float getCurrentVoltage();
    float getOutputVoltage();
};