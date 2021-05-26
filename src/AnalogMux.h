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

#ifdef UNIT_TEST
#include "ArduinoFake.h"
#else
#include "Arduino.h"
#endif

/**
 * @brief Main AnalogMux class
 * 
 */
class AnalogMux
{
public:
  AnalogMux();
  ~AnalogMux();
  // [DISCUSS] should i use `std::initializer_list` instead??
  void begin(uint8_t ain, uint8_t selectCount, uint8_t selectPins[]);
  int readChannel(uint8_t channel);
#ifdef UNIT_TEST
  uint8_t signalPin(void);
  uint8_t selectCount(void);
  uint8_t channelCount(void);
  uint8_t currentChannel(void);
#endif
private:
  uint8_t _ain;
  uint8_t *_selectPins;
  uint8_t _selectCount;
};

#endif // _ANALOG_SELECTOR_H_