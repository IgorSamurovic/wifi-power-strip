#include "http.h"
#include "wifi_connection.h"
#include "config.h"
#include "relay.h"


void setup(void) {
  delay(100); /* Need to wait for background processes to complete. Otherwise trouble with gpio.*/
      
  Serial.begin(115200,SERIAL_8N1,SERIAL_TX_ONLY); /* Use only tx, so rx can be used as GPIO */   
  RELAY_init();  
  WIFIC_init();
  HTTP_init();
}


void loop(void) {
  HTTP_process();
}
