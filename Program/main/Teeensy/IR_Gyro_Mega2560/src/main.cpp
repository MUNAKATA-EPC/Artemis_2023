#include <Arduino.h>
#include <Wire.h>

#include "../lib/MPU6050/src/I2Cdev.h"
#include "../lib/MPU6050/src/MPU6050_6Axis_MotionApps20.h"

#include "IR_Ring.h"
#include "MPU6050.h"

MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);  //Mega =======> Teensy

  MPU6050_setup();
  IRRing_setup();
}

void loop() {
  MPU6050_loop();
  IRRing_loop();

  Serial2.println(Ball_theta);
  Serial2.println("a");
  Serial2.println(Ball_radius);
  Serial2.println("b");
  Serial2.println(Gyro_Degree);
  Serial2.println("c");
}