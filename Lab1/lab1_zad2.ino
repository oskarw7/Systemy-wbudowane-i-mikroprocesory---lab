const int ledPins[]={12,11,10,9,8,7,6};
const unsigned long delayT[]={250,500,750,1000, 500};
void setup()
{
  for(int i=0; i<7; i++){
  	pinMode(ledPins[i], OUTPUT);
  }
}

void loop()
{
  for(int i=0; i<5; i++){
    if(i<4){
      digitalWrite(ledPins[i], LOW);
      delay(delayT[i]);
      digitalWrite(ledPins[i], HIGH);
    }
    else{
      for(int j=4;j<7;j++){
      	digitalWrite(ledPins[j], LOW);
      }
      delay(delayT[i]);
      for(int j=4;j<7;j++){
      	digitalWrite(ledPins[j], HIGH);
      }
    }
  }
}