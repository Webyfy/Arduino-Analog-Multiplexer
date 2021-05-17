#include "AnalogMux.h"

AnalogMux::AnalogMux(uint8_t ain, uint8_t s1, uint8_t s2, uint8_t s3) : selectPins{s1, s2, s3}, ain{ain}, selectCount{3}
{
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
}

AnalogMux::AnalogMux(uint8_t ain, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t s4) : AnalogMux(ain, s1, s2, s3)
{
    pinMode(s4, OUTPUT);
    selectPins[3] = s4;
    selectCount = 4;
}

int AnalogMux::readChannel(uint8_t channel)
{
    for (int8_t i = 0; i < selectCount; i++)
    {
        digitalWrite(selectPins[i], channel % 2);
        channel /= 2;
    }
    return analogRead(ain);
}