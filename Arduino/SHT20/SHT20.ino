#include <Wire.h>
   
#define DEVICE 0x40
#define TO_READ 4
  
byte buff[TO_READ]; 
char str[512];
int regAddress = 0xE3;
int raw_temp, raw_humi;
double temp = 0.00, humi = 0.00;


void setup() {
  Wire.begin();
  Serial.begin(9600);
//  writeTo(DEVICE, 0x2D, 0);
}


void loop() {
  readFrom(DEVICE, regAddress, TO_READ, buff);
  raw_temp = (((int)buff[0]) << 8) | buff[1];
  raw_humi = (((int)buff[2]) << 8) | buff[3];

  //we send the x y z values as a string to the serial port
  
  Serial.print("The raw data of temp, humi are:");
  sprintf(str, "%d %d", raw_temp, raw_humi);
  Serial.print(str);
  Serial.write(10);
  
  RP_calculate();
  Serial.print("temperature: "); Serial.println(temp);
  Serial.print("humidity: "); Serial.println(humi);
  Serial.println("");
  
  delay(1000);
}

void writeTo(int device, byte address, byte val) {
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.write(val);
  Wire.endTransmission();
}

void readFrom(int device, byte address, int num, byte buff[]) {
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.endTransmission();
  Wire.beginTransmission(device); 
  Wire.requestFrom(device, num);
  int i = 0;
  while(Wire.available()){ 
    buff = Wire.read(); 
    i++;
  }
  Wire.endTransmission();
}
  
void RP_calculate(){
  double temp_Buff = float(raw_temp);
  double humi_Buff = float(raw_humi);

  temp = (raw_temp/pow(2, 16))*175.72-46.85;
  humi = (raw_humi/pow(2, 16))*125-6;
}
