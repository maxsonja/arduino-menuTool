#include <LiquidCrystal.h>
#include "menuTool.h"

int bla=0;
valueItem test1("test1", bla, 50, 0);
MenuItem *p = &test1;

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

void setup() {
  Serial.being(115200);
  
  //backlight pin
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  
  //welcome screen
  lcd.begin(16, 2);
  delay(100);
  lcd.print("hello mee");
  delay(1000);
  lcd.clear();
  
  //display stuff on lcd
  test1.display(lcd);

  //test variable
  for(byte i=0; i<65;i++){
    test1.up();
    test1.update(lcd);
    delay(50);
  }
  delay(1000);
  for(byte i=0; i<23;i++){
    test1.down();
    test1.update(lcd);
    delay(50);
  }  
}

void loop() {
  if(Serial.available()){
    bla=Serial.readStringUntil('\n').toInt();
    test1.update(lcd);
  }
}
