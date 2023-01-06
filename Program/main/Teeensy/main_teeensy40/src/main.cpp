#include <Arduino.h>
#include <DSR1202.h>
#include <U8g2lib.h>
#include <Adafruit_NeoPixel.h>

#include "neopixel.h"
#include "buzzer.h"
#include "sensor.h"
#include "timer.h"
#include "motor.h"
#include "kicker.h"
#include "lcd.h"
#include "pid.h"

DSR1202 dsr1202(1);
Kicker kicker(4, 5);

void setup() {
  analogWriteResolution(10);  //0-255 to 0-1024
  Serial.begin(9600); //Teensy to PC

  //Initialize each Sensors
  Setup_Sensors();
  Setup_Neopixel();

  Setup_buzzer();

  //Initialize DSR1202
  dsr1202.Init();
}

void loop() {
  //read sensors
  Read_IR();
  Read_Gyro();
  Read_Camera();

  //bright neopixel
  Bright_NeoPixel();

  Serial.println(digitalRead(23));

  delay(10);
}