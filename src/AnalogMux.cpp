/**
 * @file AnalogMux.cpp
 * @author dhanesh (dhanesh@webyfy.com)
 * @brief Library for 8-channel and 16-channel analog multiplexer
 * @version 0.1
 * @date 2021-05-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Arduino.h"
#include "AnalogMux.h"

/**
 * @brief Constructor for 8 channel (3 select pins) analog multiplexer
 * 
 * @param ain Analog pin for reading output signal from the multiplexer
 * @param s1 Select pin 1
 * @param s2 Select pin 2
 * @param s3 Select pin 3
 */
AnalogMux::AnalogMux(uint8_t ain, uint8_t s1, uint8_t s2, uint8_t s3) : _selectPins{s1, s2, s3}, _ain{ain}, _selectCount{3}
{
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
}

/**
 * @brief Constructor for 16 channel (4 select pins) analog multiplexer
 * 
 * @param ain Analog pin for reading output signal from the multiplexer
 * @param s1 Select pin 1
 * @param s2 Select pin 2
 * @param s3 Select pin 3
 * @param s4 Select pin 4
 */
AnalogMux::AnalogMux(uint8_t ain, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t s4) : AnalogMux(ain, s1, s2, s3)
{
    pinMode(s4, OUTPUT);
    _selectPins[3] = s4;
    _selectCount = 4;
}

/**
 * @brief Get analog reading from a channel
 * 
 * @param channel which channel to read
 * @return analog reading of the channel
 */
int AnalogMux::readChannel(uint8_t channel)
{
    // select channel
    for (int8_t i = 0; i < _selectCount; i++)
    {
        digitalWrite(_selectPins[i], channel % 2);
        channel /= 2;
    }

    return analogRead(_ain);
}

// Methods for unit testing
#ifdef UNIT_TEST
/**
 * @brief Gets the analog Input Pin
 * 
 * @return analog input pin
 */
int AnalogMux::uint8_t signalPin(void)
{
    return _ain;
}

/**
   * @brief Get channel count
   * 
   * Gets the maximum number of channels possible with the 
   * given select pins
   * 
   * @return maximum channel count
   */
uint8_t channelCount(void)
{
    return 1 << _selectCount;
}

/**
   * @brief Get currently selected channel
   * 
   * @return currently selected channel number
   */
uint8_t currentChannel(void)
{
}

/**
   * @brief returns maximum number of select pins possible
   * 
   * @return length of select pin array
   */
uint8_t maxSelectPins(void)
{
    return uint8_t(sizeof(_selectPins)/sizeof(_selectPins[0]));
}
#endif