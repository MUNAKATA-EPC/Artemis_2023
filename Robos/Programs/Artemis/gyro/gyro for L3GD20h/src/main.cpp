#include <Arduino.h>
#include <Wire.h>
//シリアルモニタを起動しなければプログラムが走らない！！！

// Connect L3GD20 with SDA (A4), SCL (A5)

const byte L3GD20_ADDR = B1101010;  // SA0 = GND
//const byte L3GD20_ADDR = B1101011;// SA0 = VDD_IO

const byte L3GD20_WHOAMI = 0x0F;
const byte L3GD20_CTRL1 = 0x20;
const byte L3GD20_CTRL2 = 0x21;
const byte L3GD20_CTRL3 = 0x22;
const byte L3GD20_CTRL4 = 0x23;
const byte L3GD20_CTRL5 = 0x24;
const byte L3GD20_X_L = 0x28;
const byte L3GD20_X_H = 0x29;
const byte L3GD20_Y_L = 0x2A;
const byte L3GD20_Y_H = 0x2B;
const byte L3GD20_Z_L = 0x2C;
const byte L3GD20_Z_H = 0x2D;

#define ledpin 13
#define ledpin2 12
#define analogpin 1
#define outputpin 0
#define resetpin 6


float degdata = 0;
int i = 0;
const float caldata = 0;//←ここにキャリブレーション値のデフォルトを

void L3GD20_write(byte reg, byte val)
{
  Wire.beginTransmission(L3GD20_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();  
}

byte L3GD20_read(byte reg)
{
  byte ret = 0;
  // request the registor
  Wire.beginTransmission(L3GD20_ADDR);
  Wire.write(reg);
  Wire.endTransmission();  

  // read
  Wire.requestFrom((unsigned int)L3GD20_ADDR, 1);
  
  while (Wire.available()) {
    ret = Wire.read();
  }
  
  return ret;
}

void setup() {
  pinMode(resetpin, INPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(ledpin2, OUTPUT);

  analogWriteResolution(10);
  
  Serial.begin(9600);
  Wire.begin();
  
  Serial.println(L3GD20_read(L3GD20_WHOAMI), HEX); // should show D4

  L3GD20_write(L3GD20_CTRL1, B00001111);
                         //   |||||||+ X axis enable
                         //   ||||||+- Y axis enable
                         //   |||||+-- Z axis enable
                         //   ||||+--- PD: 0: power down, 1: active
                         //   ||++---- BW1-BW0: cut off 12.5[Hz]
                         //   ++------ DR1-DR0: ODR 95[HZ]

  L3GD20_write(L3GD20_CTRL4, B00110000);

}

void loop() {
  short Z;
  float z;
  long outputdata;
  float microcaldata = 0;
  int val = 0;
  Z = L3GD20_read(L3GD20_Z_H);
  z = Z = (Z << 8) | L3GD20_read(L3GD20_Z_L);

  //microcaldata = analogRead(analogpin);
  //microcaldata = (microcaldata - 512) / 50;
  
  degdata = degdata + z + caldata + microcaldata;
  
  outputdata = (degdata / 4096) + 512 ;
  if(outputdata > 1023 ){
    outputdata = 1023;
  }else if(outputdata < 0){
    outputdata = 0;     
  }

  val = outputdata;
  analogWrite(outputpin, val);
  if(val < 510){
    digitalWrite(ledpin, HIGH);
    digitalWrite(ledpin2, LOW);
  } else if (val < 514) {
    digitalWrite(ledpin, LOW);
    digitalWrite(ledpin2, LOW);
  } else {
    digitalWrite(ledpin, LOW);
    digitalWrite(ledpin2, HIGH);
  }
  
  if(digitalRead(resetpin) == HIGH){
    degdata = 0;
  }

  Serial.print(microcaldata);
  Serial.print("\t");
  Serial.print(val);
  Serial.print("\t");
  Serial.print(degdata);
  Serial.print("\t");
  Serial.println(outputdata);
}