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
  void begin(int8_t ain, int8_t selectCount, int8_t selectPins[],
             uint8_t switchingDelay = 0, int8_t enablePin = -1);
  int readChannel(int8_t channel);
  bool setEnable(uint8_t value);
  void selectChannel(int8_t channel);
  int read();

#ifdef UNIT_TEST
  int8_t signalPin(void);
  int8_t selectCount(void);
  int8_t channelCount(void);
  int8_t currentChannel(void);
  int8_t getEnablePin(void);
#endif
private:
  int8_t _ain;
  int8_t *_selectPins;
  int8_t _selectCount;
  int8_t _enablePin;
  uint8_t _switchingDelay;
};

#endif // _ANALOG_SELECTOR_H_
