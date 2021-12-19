#include <Arduino.h>

#if defined(ARDUINO_M5STACK_Core2)
#include <M5Core2.h>
#define SERVO_PIN_X 13
#define SERVO_PIN_Y 14
#elif defined( ARDUINO_M5STACK_FIRE )
#include <M5Stack.h>
#define SERVO_PIN_X 21
#define SERVO_PIN_Y 22
#elif defined( ARDUINO_M5Stack_Core_ESP32 )
#include <M5Stack.h>
#define SERVO_PIN_X 21
#define SERVO_PIN_Y 22
#endif

#include <Avatar.h>
#include <ServoEasing.hpp>

#define START_DEGREE_VALUE_X 90
#define START_DEGREE_VALUE_Y 90

using namespace m5avatar;

Avatar avatar;

ServoEasing servo_x;
ServoEasing servo_y;

bool random_move = false;

void setup() {
#if defined(ARDUINO_M5STACK_Core2)
  M5.begin(true, true, true, false, kMBusModeOutput);
#elif defined( ARDUINO_M5STACK_FIRE ) || defined( ARDUINO_M5Stack_Core_ESP32 )
  M5.begin(true, true, true, false);
#endif

  avatar.init();

  if (servo_x.attach(SERVO_PIN_X, START_DEGREE_VALUE_X, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE)) {
    Serial.print("Error attaching servo x");
  }
  if (servo_y.attach(SERVO_PIN_Y, START_DEGREE_VALUE_Y, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE)) {
    Serial.print("Error attaching servo y");
  }

  servo_x.setEasingType(EASE_QUADRATIC_IN_OUT);
  servo_y.setEasingType(EASE_QUADRATIC_IN_OUT);
  setSpeedForAllServos(30);
}

void loop() {
  M5.update();

  if (M5.BtnA.wasPressed()) {
    random_move = false;
    servo_x.setEaseTo(90);
    servo_y.setEaseTo(90);
    synchronizeAllServosStartAndWaitForAllServosToStop();
  }
  
  if (M5.BtnB.wasPressed()) {
    random_move = false;
    for (int i = 0; i < 2; i++) {
      servo_x.easeTo(80);
      servo_x.easeTo(100);
      servo_x.easeTo(90);
      servo_y.easeTo(80);
      servo_y.easeTo(100);
      servo_y.easeTo(90);
    }
  }

  if (M5.BtnC.wasPressed()) {
    random_move = !random_move;
  }

  if (random_move) {
    int x = 90 + random(19) - 8;
    int y = 90 + random(25) - 12;
    servo_x.setEaseTo(x);
    servo_y.setEaseTo(y);
    synchronizeAllServosStartAndWaitForAllServosToStop();
    
    int delay_time = random(10);
    delay(2000 + 100 * delay_time);
  }
}
