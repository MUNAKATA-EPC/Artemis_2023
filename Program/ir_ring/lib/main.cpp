#include <Arduino.h>

class Vector{
private:
    double x;
    double y;
public:
    double GetX(){
        return x;
    }
    double GetY(){
        return y;
    }
    void Set(double x, double y){
        this->x = x;
        this->y = y;
    }
};

class IR_Sensor{
public:
    Vector IR_Point;
    int value;
};

Vector Ball_Point;

IR_Sensor IR_Sen[8];

void Read_Sensor(){    
    IR_Sen[0].value = analogRead(2);
    IR_Sen[1].value = analogRead(3);
    IR_Sen[2].value = analogRead(4);
    IR_Sen[3].value = analogRead(5);
    IR_Sen[4].value = analogRead(6);
    IR_Sen[5].value = analogRead(10);
    IR_Sen[6].value = analogRead(9);
    IR_Sen[7].value = analogRead(8);
}

bool CheckAllSensor(){
    int test = 0;
    for(int i = 0; i < 8; i++){
        if(IR_Sen[i].value > 920){
            test++;
        }
    }
    return test == 8;
}

void setup(){
    Serial.begin(9600);

    IR_Sen[0].IR_Point.Set(0.382, 0.923);
    IR_Sen[1].IR_Point.Set(0.923, 0.382);
    IR_Sen[2].IR_Point.Set(0.923, -0.382);
    IR_Sen[3].IR_Point.Set(0.382, -0.923);
    IR_Sen[4].IR_Point.Set(-0.382, -0.923);
    IR_Sen[5].IR_Point.Set(-0.923, -0.382);
    IR_Sen[6].IR_Point.Set(-0.923, 0.382);
    IR_Sen[7].IR_Point.Set(-0.382, 0.923);
}

void loop(){
    Read_Sensor();

    Ball_Point.Set(0, 0);
    for(int i = 0; i < 8; i++){
        if(!CheckAllSensor())
            Ball_Point.Set( Ball_Point.GetX() + IR_Sen[i].IR_Point.GetX() * (920 - IR_Sen[i].value), 
                            Ball_Point.GetY() + IR_Sen[i].IR_Point.GetY() * (920 - IR_Sen[i].value));
        else 
            Ball_Point.Set(0, 0);
    }

    int a = atan2(Ball_Point.GetY(), Ball_Point.GetX()) / 3.14 * 180;   //ベクトルを角度に変換
    a = a > 0 ? a : a + 360;    //0~360に補正
    a = 360 - a + 90 + 22;   //中心を0にしよう IRの一個目が22度ずれてるから調整
    a = a > 360 ? a - 360 : a;
    a = a / 5;
    a = a * 5;
    /*
    for(int i = 0; i < 8; i++){
        Serial.print(IR_Sen[i].value);
        Serial.print(", ");
    }
    Serial.println();*/
    Serial.print(Ball_Point.GetX());
    Serial.print(", ");
    Serial.print(Ball_Point.GetY());
    Serial.print(", ");
    Serial.println(a);
    
    if(Ball_Point.GetX() == 0 && Ball_Point.GetY() == 0)
        analogWrite(0, 1023);
    else
        analogWrite(0, (a > 340) ? 0 : a * 2);
}