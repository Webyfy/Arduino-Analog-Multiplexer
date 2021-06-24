#include <Arduino.h>
#include "AnalogMux.h"

#define S1 4
#define S2 5
#define S3 6
#define AIN A0
#define AREF 5

#define POLL_INTERVAL 1000
#define SERIAL_BAUD_RATE 115200

#define MUX_SWITCHING_DELAY 1


AnalogMux am;
int8_t activeChannels[]{0, 1, 2, 3, 4, 5, 6, 7};

float mapFloat(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow; 
}

void setup() {
  int8_t selectPins[]{S1, S2, S3};
  am.begin(AIN, 3, selectPins, MUX_SWITCHING_DELAY);
  Serial.begin(SERIAL_BAUD_RATE);
}

void loop() {
  for (int8_t i = 0; i < (sizeof(activeChannels)/sizeof(activeChannels[0])); i++)
  {
    Serial.print(activeChannels[i]);
    Serial.print(F(" => "));
    int value = am.readChannel(activeChannels[i]);
    Serial.print(mapFloat(value, 0, 1023, 0, AREF));
    Serial.print(F("v; \t"));
  }
  Serial.println();
  delay(POLL_INTERVAL);
}
