#include <Arduino.h>
#include <DSR1202.h>
#include <U8g2lib.h>
#include <Adafruit_NeoPixel.h>

#include "sensor.h"
#include "timer.h"
#include "motor.h"
#include "lcd.h"
#include "pid.h"

DSR1202 dsr1202(1);

void setup() {
  analogWriteResolution(10);  //0-255 to 0-1024
  Serial.begin(9600); //Teensy to PC

  //Initialize each Sensors
  Setup_Sensors();

  //Initialize DSR1202
  dsr1202.Init();
}

void loop() {
  //read sensors
  Read_IR();
  Read_Gyro();
  Read_Camera();

  delay(10);
}