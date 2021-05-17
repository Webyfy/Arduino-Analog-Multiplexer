#include <Arduino.h>
#include "AnalogMux.h"

#define S1 4
#define S2 5
#define S3 6
#define AIN A0

#define POLL_INTERVAL 1000
#define SERIAL_BAUD_RATE 115200

AnalogMux as = AnalogMux(S1, S2, S3, AIN);
uint8_t activeChannels[]{0, 1, 2, 3, 4, 5, 6, 7};

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
}

void loop() {
  for (uint8_t i = 0; i < (sizeof(activeChannels)/sizeof(activeChannels[0])); i++)
  {
    Serial.print(activeChannels[i]);
    Serial.print(F(" : "));
    Serial.print(as.readChannel(activeChannels[i]));
    Serial.print(F("\t"));
  }
  Serial.println();
  
}