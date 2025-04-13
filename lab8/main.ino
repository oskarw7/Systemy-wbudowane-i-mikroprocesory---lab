#include "MFRC522.h"
#include <stdio.h>
#include <SPI.h>

#define RED_LED_PIN 2
#define GREEN_LED_PIN 3
#define BUZZER_PIN A5

MFRC522 rfid(10, 9);
MFRC522::MIFARE_Key key;

uint8_t key[4];
const uint8_t target_key = {0x01, 0x01, 0x01, 0x01}; 
unsigned long lastReadTime = 0;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  

  rfid.PCD_Init();
  SPI.begin();

  Serial.begin(9600);
}

void display_key(){
  Serial.println("Read key:");
  for(int i=0;i<4;i++){
    Serial.print(key[i]);
  }
  Serial.println();
}

void match_keys() {
  for(int i=0;i<4;i++){
    if(target_key[i] != key[i]){
      return False;
    }
  }
  return True;
}

void loop() {
  if(rfid.PICC_IsNewCardPresent && rfid.PICC_ReadCardSerial()) {
    for(int i = 0; i < 4; i++){
      key[i] = rfid.uid.uidByte[i];
    }

    display_key();

    if(match_keys()){
      digitalWrite(GREEN_LED_PIN, HIGH);
      tone(BUZZER_PIN, 900);
    } else {
      digitalWrite(RED_LED_PIN, HIGH);
      tone(BUZZER_PIN, 200);
    }

    lastReadTime = millis();
  }

  if(lastReadTime - millis() > 1000) {
    noTone(BUZZER_PIN);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);

  }

}
