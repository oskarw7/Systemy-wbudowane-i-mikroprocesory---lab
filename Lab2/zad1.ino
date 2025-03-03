/*
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D
*/

const byte segmentValues[11][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0}, //0
  {0, 1, 1, 0, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1, 0}, //2
  {1, 1, 1, 1, 0, 0, 1, 0}, //3
  {0, 1, 1, 0, 0, 1, 1, 0}, //4
  {1, 0, 1, 1, 0, 1, 1, 0}, //5
  {1, 0, 1, 1, 1, 1, 1, 1}, //6
  {1, 1, 1, 0, 0, 0, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1, 0}, //8
  {1, 1, 1, 1, 0, 1, 1, 1}, //9
  {0, 0, 0, 0, 0, 0, 0, 0}  //off
};

const int segmentPins[8] = {2,3,4,5,6,7,8,9};
const int segmentPinsCount = 8;

const int digitPins[4] = {15,16,17,18};
const int digitPinsCount = 4;

const int rowPins[4] = {14,13,12,11};
const int rowPinsCount = 4;


int displayState[4] = {2, 6, 1, 7};

void display() {
  for(int i = 0; i<4; i++) {
    digitalWrite(digitPins[i], LOW);
  }
  for(int j = 0;j < 4;j++){
    const int number = displayState[j];
    
    for(int i = 0; i < 8; i++) {
      digitalWrite(segmentPins[i], !segmentValues[number][i]);
    }

    digitalWrite(digitPins[j], HIGH);
    delayMicroseconds(50);
    digitalWrite(digitPins[j], LOW);
  }
  for(int i = 0; i < 8; i++){
    digitalWrite(segmentPins[i], HIGH);
  }
}

void setup() {
  for(int i = 0; i < segmentPinsCount; i++){
    pinMode(segmentPins[i], OUTPUT);
    //digitalWrite(segmentPins[i], LOW);
  }
  for(int i = 0; i < digitPinsCount; i++){
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], LOW);
  }
  for(int i = 0; i < rowPinsCount; i++){
    pinMode(rowPins[i], INPUT_PULLUP);
  }
}

void loop() {
  display();
}
