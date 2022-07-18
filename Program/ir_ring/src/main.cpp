#include <Arduino.h>

void setup() {
  Serial.begin(9600);

  pinMode(1, INPUT);
}

void loop() {
  Serial.println(analogRead(1));
  delay(10);
}