#include <MENU.h>
Menu test;
String s[5]={"time", "weather", "arduino", "esp32", "esp8266"};

void setup() {
  // put your setup code here, to run once:
  test.Begin(2,3,45,3,"--",0);
  test.Inputstring(s,5,0);
  test.Inputfun_0("abb","bcc","cdd");
  test.Inputfun_1("f","e","f");
  test.Inputfun_2("fe","h","i");
  test.Inputfun_3("1","k","l");
  test.Inputfun_4("24","n","o");
}

void loop() {
  // put your main code here, to run repeatedly:
  test.Loop();
}
