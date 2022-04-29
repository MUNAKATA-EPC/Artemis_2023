#include <Arduino.h>
#include <Wire.h>

const byte GYRO_ADDR = 0x6B;
const byte GYRO_WHOAMI = 0x0F;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(GYRO_ADDR);
  Wire.write(GYRO_WHOAMI);
  Wire.endTransmission();

  Wire.requestFrom(GYRO_ADDR, 1);
  Serial.println(Wire.read());
  delay(1000);
}