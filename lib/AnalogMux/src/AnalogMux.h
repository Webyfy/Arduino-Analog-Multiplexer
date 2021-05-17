#ifndef _ANALOG_SELECTOR_H_
#define _ANALOG_SELECTOR_H_

#include <Arduino.h>

class AnalogMux
{
public:
    AnalogMux(uint8_t ain, uint8_t s1, uint8_t s2, uint8_t s3);
    // more readable than polymorphism
    AnalogMux(uint8_t ain, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t s4);
    int readChannel(uint8_t channel);

private:
    uint8_t ain;
    uint8_t selectPins[4];
    int8_t selectCount;
};

#endif // _ANALOG_SELECTOR_H_