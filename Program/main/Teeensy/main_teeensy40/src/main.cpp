#include <Arduino.h>
#include <DSR1202.h>
#include <U8g2lib.h>
#include <Adafruit_NeoPixel.h>

#include "pins.h"
#include "neopixel.h"
#include "buzzer.h"
#include "sensor.h"
#include "timer.h"
#include "motor.h"
#include "kicker.h"
#include "lcd.h"
#include "pid.h"

DSR1202 dsr1202(1);

void setup() {
  dsr1202.Init();
}

void loop() {
  dsr1202.move(20, 20, 20, 20);
}