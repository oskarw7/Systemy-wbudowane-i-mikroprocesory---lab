#include <LiquidCrystal.h>

LiquidCrystal LCD(12,11,5,4,3,2);
String text = "";

byte mesh[8] = { 0b10101, 0b01010, 0b10101, 0b01010, 0b10101, 0b01010, 0b10101, 0b01010 };

int position[2] = {0,0};

void manageCommand(){
  if(text == "right"){
    position[0]++;
    if(position[0] == 16){
    	position[0]--;
      Serial.println("wall");
    }
  }
  if(text == "up"){
    position[1]--;
    if(position[1] == 0){
    	position[1]++;
      Serial.println("wall");
    }
  }
  if(text == "down"){
    position[1]++;
    if(position[1] == 2){
    	position[1]--;
      Serial.println("wall");
    }
  }
  if(text == "left"){
    position[0]--;
    if(position[0] == 0){
    	position[0]++;
      Serial.println("wall");
    }
  }
}

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
  	LCD.setCursor(position[0], position[1]);
  	LCD.write("\1");
    text="";
  }
}

void setup(){
  Serial.begin(9600);
  Serial.println("Awaiting commands...");
  
  LCD.begin(16,2);
  LCD.createChar(1, mesh)
  LCD.clear();
  
  LCD.setCursor(0,0);
  LCD.write("\1");

}

void loop(){
  readString();
  manageCommand();
  writeString();
}
