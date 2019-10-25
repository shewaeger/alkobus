
#include <avr/io.h>

class VoltageControl{

private:
    float currentVoltage;
    float trueOutputVoltage;
    uint16_t dimming;

    void reMathDimming();

    static float reMathVoltage(double value);

public:
    void setup();
    void loop();

    void setVoltage(float voltage);
    float getCurrentVoltage();

    static float getInputVoltage();
};