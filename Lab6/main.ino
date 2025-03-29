#include <LiquidCrystal.h>

#define PIR_PIN 10
#define TRIG_PIN 8
#define ECHO_PIN 9

bool dataChanged = true;
bool moving = false;
int sensedDistance = 0;

const double microsToDistanceRatio = 29.1*2;
const unsigned int upperDistanceLimit = 200;
const unsigned long measureTimeoutMicros = ceil(upperDistanceLimit * microsToDistanceRatio);
unsigned long lastDebounceTime = 0;

LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(PIR_PIN, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  pinMode(ECHO_PIN, INPUT);

  LCD.begin(16, 2);
  LCD.clear();
}

void updateLCD() {
    if(dataChanged){
        LCD.clear();

        LCD.setCursor(0,0);
        LCD.print(moving ? "ruch" : "brak ruchu");
        
        LCD.setCursor(0,1);
        LCD.print("dist: ");
        LCD.print(sensedDistance > 0 ? sensedDistance : "OoR");
        LCD.print("cm");

        dataChanged = false;
    }
}


void readMovement() {
    int input = digitalRead(PIR_PIN);

    moving = false;
    
    if(input == HIGH){
        if(millis() - lastDebounceTime > 500){
            lastDebounceTime = millis();

            dataChanged = moving ^ input;
            moving = true;
        }
    }
}

void readDistance() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  int duration = pulseIn(ECHO_PIN, HIGH, measureTimeoutMicros);
  sensedDistance = duration / microsToDistanceRatio;
  dataChanged = true;
}

void loop() {
  readMovement();
  readDistance();
  updateLCD();
}