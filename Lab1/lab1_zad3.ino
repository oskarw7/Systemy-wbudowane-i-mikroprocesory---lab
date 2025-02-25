// C++ code
//
const int ledPins[]={12,11,10,9};
const int rgbPins[]={8,7,6};
const int btnPins[]={1,2,3,4};

int ledStates[]={HIGH,HIGH,HIGH,HIGH};
int btnStates[]={HIGH,HIGH,HIGH,HIGH};

int rgbState=0;
unsigned long lastT=0;
const unsigned long interval=200;

void setup()
{
  for(int i=0; i<4; i++){
  	pinMode(ledPins[i], OUTPUT);
  }
  for(int i=0; i<3; i++){
  	pinMode(rgbPins[i], OUTPUT);
  }
  for(int i=0; i<4; i++){
  	pinMode(btnPins[i], INPUT_PULLUP);
  }
}

void loop()
{
  for(int i=0; i<4; i++){
    int input = digitalRead(btnPins[i]);
    if(input!=btnStates[i]){
    	delay(20);
      	btnStates[i]=input;
        if(btnStates[i]==LOW){
          switch(btnPins[i]){
          	case 1:
            	ledStates[0]=!ledStates[0];
            	break;
            case 2:
            	ledStates[1]=!ledStates[1];
            	break;
            case 3:
            	ledStates[2]=!ledStates[2];
            	break;
            case 4:
            	ledStates[3]=!ledStates[3];
            	break;
          }
        }
    }
    digitalWrite(ledPins[i], ledStates[i]);
  }
  unsigned long currentT = millis();
  if(currentT-lastT>interval){
    lastT=currentT;
    digitalWrite(rgbPins[0], (rgbState&0b100)?LOW:HIGH);
    digitalWrite(rgbPins[1], (rgbState&0b010)?LOW:HIGH);
    digitalWrite(rgbPins[2], (rgbState&0b001)?LOW:HIGH);
    rgbState++;
    if(rgbState>7){
      rgbState=0;
    }
  }
}