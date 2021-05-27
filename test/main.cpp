/**
 * @file main.cpp
 * @author dhanesh (dhanesh@webyfy.com)
 * @brief Unit Testing for AnalogMux
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Copyright (c) 2021
 * 
 * License:
 *  This project is in the public domain.
 * 
 */

#include <unity.h>
#include <AnalogMux.h>

using namespace fakeit;

void setUp(void)
{
  ArduinoFakeReset();
}

void tearDown(void)
{
}

/**
 * @brief tests mux initialization
 * 
 */
void test_Mux_init(void)
{
  When(Method(ArduinoFake(), pinMode)).AlwaysReturn();
  When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();

  AnalogMux mux;
  int8_t selectPins[]{8, 9, 10, 11, 12};
  int8_t len = sizeof(selectPins) / sizeof(selectPins[0]);
  mux.begin(A0, len, selectPins);

  TEST_ASSERT_EQUAL(A0, mux.signalPin());

  Verify(Method(ArduinoFake(), pinMode).Using(8, OUTPUT)).Once();
  Verify(Method(ArduinoFake(), pinMode).Using(9, OUTPUT)).Once();
  Verify(Method(ArduinoFake(), pinMode).Using(10, OUTPUT)).Once();
  Verify(Method(ArduinoFake(), pinMode).Using(11, OUTPUT)).Once();
  Verify(Method(ArduinoFake(), pinMode).Using(12, OUTPUT)).Once();

  TEST_ASSERT_EQUAL(32, mux.channelCount());
}

/**
 * @brief tests channel selection and analog read
 * 
 */
void test_Mux_read(void)
{
  When(Method(ArduinoFake(), pinMode)).AlwaysReturn();
  When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
  When(Method(ArduinoFake(), analogRead)).AlwaysReturn();

  // s1 = 8, s2 = 9, s3 = 10
  int8_t ain{A0}, selectPins[]{8, 9, 10}, selectCount{3};
  AnalogMux mux;
  mux.begin(ain, selectCount,selectPins);

  mux.readChannel(3); // (s3 - 0), (s2 - 1), (s1 - 0)

  Verify(Method(ArduinoFake(), digitalWrite).Using(selectPins[2], LOW)).Once();
  Verify(Method(ArduinoFake(), digitalWrite).Using(selectPins[1], HIGH)).Once();
  Verify(Method(ArduinoFake(), digitalWrite).Using(selectPins[0], HIGH)).Once();
  Verify(Method(ArduinoFake(), analogRead).Using(A0)).Once();

}

/**
 * @brief Test enable pin 
 * 
 * Tests set enable with and without initilization
 * 
 */
void test_Enable(void)
{
  When(Method(ArduinoFake(), pinMode)).AlwaysReturn();
  When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();

  AnalogMux mux;

  TEST_ASSERT_EQUAL(-1, mux.getEnablePin());

  TEST_ASSERT_EQUAL(false, mux.setEnable(HIGH));
  Verify(Method(ArduinoFake(), digitalWrite).Using(-1, _)).Never();

  int8_t selectPins[]{8, 9, 10};
  int8_t enablePin = 12;
  int8_t selectCount = sizeof(selectPins) / sizeof(selectPins[0]);
  mux.begin(A0, selectCount, selectPins, enablePin);

  TEST_ASSERT_EQUAL(enablePin, mux.getEnablePin());
  Verify(Method(ArduinoFake(), pinMode).Using(enablePin, OUTPUT)).Once();

  TEST_ASSERT_EQUAL(true, mux.setEnable(HIGH));
  Verify(Method(ArduinoFake(), digitalWrite).Using(enablePin, HIGH)).Once();
}
int main(int argc, char **argv)
{
  UNITY_BEGIN();

  RUN_TEST(test_Mux_init);
  RUN_TEST(test_Mux_read);
  RUN_TEST(test_Enable);

  return UNITY_END();
}
