#include <LiquidCrystal.h>

LiquidCrystal LCD(12,11,5,4,3,2);
String text = "";

byte mesh[8] = { 0b10101, 0b01010, 0b10101, 0b01010, 0b10101, 0b01010, 0b10101, 0b01010 };

void readString(){
  if(Serial.available() > 0){
    text = Serial.readStringUntil('\n');
    if(text.length() > 16){
      Serial.println("Too many chars.");
    }
  }
}

void writeString(){
  if(text.length()){
    LCD.clear();
    for(int i = 0; i < text.length(); i++){
      LCD.write(text[i]);
    }
    LCD.write("\1");
    text="";
  }
}

void setup(){
  LCD.begin(16,2);
  LCD.clear();
  LCD.setCursor(0,0);
  Serial.begin(9600);
  LCD.createChar(1, mesh);
}

void loop(){
  readString();
  writeString();
}
