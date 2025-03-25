#include <LiquidCrystal.h>
#include <TimerOne.h>

LiquidCrystal LCD (12,11,7,6,5,4);

const int pinSwitch1 = 8;
const int pinSwitch2 = 2;

unsigned long lastDebounceTime = 0;
int lastButtonState = 0;
double data = 0.0;
bool dataChanged = false;
bool modeChanged = false;
int currentMode = 0;
// 0 - timer mode
// 1 - button mode

void setup(){
  pinMode(pinSwitch1, INPUT_PULLUP);
  pinMode(pinSwitch2, INPUT_PULLUP);

  Timer1.initialize(500000);

  LCD.begin(16,2);
  LCD.clear();
  LCD.setCursor(0,0);
}

void printData(){
  if(dataChanged || modeChanged){
    LCD.clear();
    LCD.setCursor(0,0);
    LCD.print("Voltage: ");
    LCD.print(data);
    LCD.setCursor(0,1);
    LCD.print(currentMode == 0 ? "Timer" : "Button");
    dataChanged = false;
    modeChanged = false;
  }
}

void readData(){
  data = analogRead(A5)/1024.0 * 5;
  dataChanged = true;
}

void readDataButton(){
  Timer1.detachInterrupt();
  attachInterrupt(digitalPinToInterrupt(pinSwitch2), readData, FALLING);
}

void readDataTimer(){
  detachInterrupt(digitalPinToInterrupt(pinSwitch2));
  Timer1.attachInterrupt(readData);
}

void readButton(){
  int input = digitalRead(pinSwitch1);

  if(millis() - lastDebounceTime > 50) {
    lastDebounceTime = millis();
    if(lastButtonState != input){
    if(input == LOW){
      currentMode = currentMode == 0 ? 1 : 0;
      modeChanged = true;
      switch(currentMode){
        case 0:
          readDataTimer();
          break;
        case 1:
          readDataButton();
          break;
        default:
          break;
      }
  }
  }
  lastButtonState = input;
  }


}

void loop(){
  readButton();
  printData();
}
