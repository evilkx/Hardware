#include <SCServo.h>

SCSCL sc;

void setup()
{
  Serial.begin(1000000);
  sc.pSerial = &Serial;
}

void loop()
{
  sc.WritePos(1, 1023, 2000);//舵机(ID1),运行至1023位置,运行时间T=2000ms
  sc.WritePos(2, 1023, 100);//舵机(ID2),运行至1023位置,运行时间T=2000ms
  sc.WritePos(3, 1023, 100);//舵机(ID3),运行至1023位置,运行时间T=2000ms
  sc.WritePos(4, 1023, 100);//舵机(ID4),运行至1023位置,运行时间T=2000ms
  delay(2100); 
  sc.WritePos(1, 0, 2000);//舵机(ID1),运行至0位置,运行时间T=2000ms
  sc.WritePos(2, 0, 100);//舵机(ID2),运行至0位置,运行时间T=2000ms
  sc.WritePos(3, 0, 100);//舵机(ID3),运行至1023位置,运行时间T=2000ms
  sc.WritePos(4, 0, 100);//舵机(ID4),运行至1023位置,运行时间T=2000ms
  delay(2100);
  
}
