#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);
unsigned char data=0x00;

void read1(){
  mySerial.write(0xAA);
  mySerial.write(0x07);
  mySerial.write(0x02);
  mySerial.write(data);
  mySerial.write(0x01);
  mySerial.write(0xB4);
}

void read2(){
  mySerial.write(0xAA);
  mySerial.write(0x07);
  mySerial.write(0x02);
  mySerial.write(data);
  mySerial.write(0x02);
  mySerial.write(0xB5);
}

void read3(){
  mySerial.write(0xAA);
  mySerial.write(0x07);
  mySerial.write(0x02);
  mySerial.write(data);
  mySerial.write(0x03);
  mySerial.write(0xB6);
}

void read4(){
  mySerial.write(0xAA);
  mySerial.write(0x07);
  mySerial.write(0x02);
  mySerial.write(data);
  mySerial.write(0x04);
  mySerial.write(0xB7);
}

void read5(){
  mySerial.write(0xAA);
  mySerial.write(0x07);
  mySerial.write(0x02);
  mySerial.write(data);
  mySerial.write(0x05);
  mySerial.write(0xB8);
}

void read6(){
  mySerial.write(0xAA);
  mySerial.write(0x07);
  mySerial.write(0x02);
  mySerial.write(data);
  mySerial.write(0x06);
  mySerial.write(0xB9);
}

void setup() {
  mySerial.begin(9600);  //以9600波特率打开软串口
}

void loop() {

  read1();
  delay(3000);
  read2();
  delay(3000);
  read3();
  delay(3000);
  read4();
  delay(3000);
  read5();
  delay(3000);
  read6();
  delay(3000);
  
}
