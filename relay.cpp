#include <Arduino.h>
#include <ESP_EEPROM.h>
#include "http.h"
#include "config.h"
#include "relay.h"


uint8_t currentState = 0;
int pinMap[] = {RELAY_1_PIN, RELAY_2_PIN, RELAY_3_PIN, RELAY_4_PIN, RELAY_5_PIN, RELAY_6_PIN};


void saveState(){
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.put(SAVED_STATE_ADDR, currentState);
  boolean ok = EEPROM.commit();
  Serial.println((ok) ? "Commit to EEPROM OK" : "Commit to EEPROM failed");
}

uint8_t readSavedStateFromEEPROM(void){
  uint8_t savedState;
  
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(SAVED_STATE_ADDR, savedState);
  Serial.print("Read saved state of relays from EEPROM:");
  Serial.println(savedState);  

  return savedState;
}

uint8_t RELAY_getCurrentState(uint8_t relay_id){
  uint8_t relayState = (currentState >> relay_id) & 1;
  return relayState;
}

void RELAY_set_all( uint8_t value){
  currentState = value;
  
  for(int i = 0; i < NUMBER_OF_RELAYS; i++){
    int relayVal = (value >> i) & 1;
    
    digitalWrite(pinMap[i], relayVal);
  }

  saveState();
}

int RELAY_set_id( uint8_t relay_id, uint8_t value ){
  if(relay_id < NUMBER_OF_RELAYS){
    digitalWrite(pinMap[relay_id], (value & 1));
    
    uint8_t newVal = (value & 1) << relay_id;
    uint8_t clearMask = ~(1 << relay_id);

    currentState = (currentState & clearMask) | newVal;

    saveState();
    return 0;
  }else{
    Serial.println("ERROR: Invalid relay ID");
  }
  return 1;
}


void RELAY_init(void){  
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(RELAY_3_PIN, OUTPUT);
  pinMode(RELAY_4_PIN, OUTPUT);
  pinMode(RELAY_5_PIN, OUTPUT);
  pinMode(RELAY_6_PIN, OUTPUT);
   
  uint8_t savedState = readSavedStateFromEEPROM();
  RELAY_set_all(savedState);  
}
