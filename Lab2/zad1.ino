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

const byte segmentValues[15][8] = {
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
  {0, 0, 0, 0, 0, 0, 0, 0}, //off
  {1, 1, 1, 0, 1, 1, 1, 0}, //A
  {0, 0, 1, 1, 1, 1, 1, 0}, //B
  {0, 0, 0, 1, 1, 0, 1, 0}, //C
  {0, 1, 1, 1, 1, 0, 1, 0}  //D
};

const int segmentPins[8] = {2,3,4,5,6,7,8,9};
const int segmentPinsCount = 8;

const int digitPins[4] = {15,16,17,18};
const int digitPinsCount = 4;

const int rowPins[4] = {14,13,12,11};
const int rowPinsCount = 4;


int displayState[4] = {2, 8, 1, 7};
const int sequenceSize = 4;

int sequence1[4] = {2, 8, 1, 7};
int sequence2[4] = {3, 4, 5, 6};

int previousKeyState[digitPinsCount * rowPinsCount];
int iter = 0;
byte full = false;

void pushKey(int key) {
  switch(key){
    case 'A':
      key = 11;
      break;
    case 'B':
      key = 12;
      break;
    case 'C':
      key = 13;
      break;
    case 'D':
      key = 14;
      break;
  }
  displayState[iter] = key;
  iter = (iter + 1) % 4;
}

void display() {
  for(int i = 0; i<4; i++) {
    digitalWrite(digitPins[i], LOW);
  }
  for(int j = 0;j < 4;j++){
    const int number = displayState[j];

    for(int i = 0; i < 8; i++)
      digitalWrite(segmentPins[i], !segmentValues[number][i]);

    digitalWrite(digitPins[j], HIGH);
    delayMicroseconds(50);
    digitalWrite(digitPins[j], LOW);
  }
  for(int i = 0; i < 8; i++)
    digitalWrite(segmentPins[i], HIGH);

}

int mapKey(int sum){
  int mapTo;
  switch(sum){
    case 0:
      mapTo = 'A';
      break;
    case 1:
      mapTo = 'B';
      break;
    case 2:
      mapTo = 'C';
      break;
    case 3:
      mapTo = 'D';
      break;
    case 4:
      mapTo = 3;
      break;
    case 5:
      mapTo = 6;
      break;
    case 6:
      mapTo = 9;
      break;
    case 7:
      mapTo = '#';
      break;
    case 8:
      mapTo = 2;
      break;
    case 9:
      mapTo = 5;
      break;
    case 10:
      mapTo = 8;
      break;
    case 11:
      mapTo = 0;
      break;
    case 12:
      mapTo = 1;
      break;
    case 13:
      mapTo = 4;
      break;
    case 14:
      mapTo = 7;
      break;
    case 15:
      mapTo = '*';
      break;
    default:
      mapTo = -1;
      break;
  }
  return mapTo;
}

void manageSequence(int key){
  int* currentSequence = nullptr;
  if(key=='*'){
    currentSequence = sequence1;
  }
  else if (key=='#'){
    currentSequence = sequence2;
  }
  if(currentSequence != nullptr)
    for(int i=0; i<sequenceSize; i++)
      displayState[i] = currentSequence[i];

}

void readKey(){
  if(displayState[3] != 10){
    full = true;
  }

  for(int i=0; i<digitPinsCount; i++)
    digitalWrite(digitPins[i], HIGH);

  for(int i = 0; i < digitPinsCount; i++){
    digitalWrite(digitPins[i], LOW);

    for(int j = 0; j < rowPinsCount; j++){
      int input = digitalRead(rowPins[j]);

      if(input==LOW && previousKeyState[i * digitPinsCount + j] == HIGH){
          if(full == true){
            for(int k = 0; k < 4; k++)
              displayState[k] = 10;
            iter=0;
            full = false;
            break;
          }
        int key = mapKey(i*digitPinsCount+j);
        if(key == '*' || key == '#'){
          manageSequence(key);
        }
        // ^ funkcja, zeby latwiej bylo zmienic na wybieranie wszystkich przyciskow
        else if (key >= 0) {
          pushKey(key);
        }
      }
      previousKeyState[i*digitPinsCount+j] = input;
    }
    digitalWrite(digitPins[i], HIGH);
  }
}

void setup() {
  for(int i = 0; i < segmentPinsCount; i++){
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW);
  }
  for(int i = 0; i < digitPinsCount; i++){
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], LOW);
  }
  for(int i = 0; i < rowPinsCount; i++){
    pinMode(rowPins[i], INPUT_PULLUP);
  }
  for(int i =0; i<digitPinsCount*rowPinsCount; i++){
    previousKeyState[i] = HIGH;
  }
}

void loop() {
  readKey();
  display();
}