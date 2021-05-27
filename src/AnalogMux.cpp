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
 * @brief Default Constructor
 */
AnalogMux::AnalogMux() : _selectCount{0}, _enablePin{-1}
{
}

/**
 * @brief Destroy the Analog Mux:: Analog Mux object
 * 
 */
AnalogMux::~AnalogMux()
{
    if (_selectPins != nullptr)
    {
        delete[] _selectPins;
    }
}

/**
 * @brief Setup analog input pins and select pins
 * 
 * @param ain Analog Pin for reading output signal from the multiplexer
 * @param selectCount count of select pins
 * @param selectPins array of select pins
 * @param enablePin  enable pin # (optional, pass -1 if unused).
 */

void AnalogMux::begin(int8_t ain, int8_t selectCount, int8_t selectPins[], int8_t enablePin)
{
    _ain = ain;
    _selectCount = selectCount;
    _selectPins = new int8_t[selectCount];
    for (int i = 0; i < selectCount; i++)
    {
        _selectPins[i] = selectPins[i];
        pinMode(selectPins[i], OUTPUT);
    }
    if (enablePin >= 0)
    {
        _enablePin = enablePin;
        pinMode(enablePin, OUTPUT);
    }
}

/**
 * @brief Get analog reading from a channel
 * 
 * @param channel which channel to read
 * @return analog reading of the channel
 */
int AnalogMux::readChannel(int8_t channel)
{
    // select channel
    for (int8_t i = 0; i < _selectCount; i++)
    {
        digitalWrite(_selectPins[i], channel % 2);
        channel /= 2;
    }

    return analogRead(_ain);
}

/**
 * @brief sets value for enable pin
 * 
 * @param value value to write 
 * @return success of the operaton 
 * @return false 
 */
bool AnalogMux::setEnable(uint8_t value)
{
    if (_enablePin < 0)
    {
        return false;
    }
    digitalWrite(_enablePin, value);
    return true;
}
// Methods for unit testing
#ifdef UNIT_TEST
/**
 * @brief Gets the analog Input Pin
 * 
 * @return analog input pin
 */
int8_t AnalogMux::signalPin(void)
{
    return _ain;
}

/**
 * @brief get the number of select pins
 * 
 * @return the number of select pins
 */
int8_t AnalogMux::selectCount(void)
{
    return _selectCount;
}

/**
   * @brief Get channel count
   * 
   * Gets the maximum number of channels possible with the 
   * given select pins
   * 
   * @return maximum channel count
   */
int8_t AnalogMux::channelCount(void)
{
    return 1 << _selectCount;
}

/**
   * @brief Get currently selected channel
   * 
   * @return currently selected channel number
   */
int8_t AnalogMux::currentChannel(void)
{
    int8_t channel = 0;
    for (int8_t i = 0; i < _selectCount; i++)
    {
        channel += (1 << i) * digitalRead(_selectPins[i]);
    }

    return channel;
}

/**
 * @brief Get the Enable Pin 
 * 
 * @return enable pin 
 */
int8_t AnalogMux::getEnablePin(void)
{
    return _enablePin;
}

#endif
