/**
 * @file AnalogMux.h
 * @author dhanesh (dhanesh@webyfy.com)
 * @brief Library for 8-channel and 16-channel analog multiplexer
 * @version 0.1
 * @date 2021-05-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _ANALOG_SELECTOR_H_
#define _ANALOG_SELECTOR_H_

#include "Arduino.h"

/**
 * @brief Main AnalogMux class
 * 
 */
class AnalogMux
{
public:
    AnalogMux(uint8_t ain, uint8_t s1, uint8_t s2, uint8_t s3);
    AnalogMux(uint8_t ain, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t s4);
    int readChannel(uint8_t channel);

private:
    uint8_t _ain;
    uint8_t _selectPins[4];
    int8_t _selectCount;
};

#endif // _ANALOG_SELECTOR_H_