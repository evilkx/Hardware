#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
//
const int btn_UP    =   2; 
const int btn_DOWN  =   3; 
const int btn_LEFT  =   4; 
const int btn_RIGHT =   5; 

String btn_s = "button is ";

int v=3;
int h=7;

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

void setup(void) {
  u8g2.begin();
  u8g2.enableUTF8Print(); 
  pinMode(btn_UP, INPUT);
  pinMode(btn_DOWN, INPUT);
  pinMode(btn_LEFT, INPUT);
  pinMode(btn_RIGHT, INPUT);
}
 
void loop(void) {
//  btnd_State = digitalRead(btn_DOWN);
//  btnu_State = digitalRead(btn_UP);
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  
  if(digitalRead(btn_DOWN) == HIGH){
    delay(45);
    if (digitalRead(btn_DOWN) == HIGH){
      h += 10;   
    }
  }
  if (digitalRead(btn_UP) == HIGH){
    delay(45);
    if (digitalRead(btn_UP) == HIGH){
      h -= 10;   
    }
  }
    if(digitalRead(btn_RIGHT) == HIGH){
    delay(45);
    if (digitalRead(btn_RIGHT) == HIGH){
      v += 10;   
    }
  }
  if (digitalRead(btn_LEFT) == HIGH){
    delay(45);
    if (digitalRead(btn_LEFT) == HIGH){
      v -= 10;   
    }
  }
  u8g2.drawBox(v,h,15,15);
  u8g2.drawRFrame(3,3,121,61,2);
//  u8g2.drawStr(0,30,btn_s.concat(btnd_State)); 
  u8g2.drawStr(0,40,"vilogy"); 
  
  u8g2.sendBuffer();

}
