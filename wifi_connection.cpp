#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "config.h"


void WIFIC_init(void){   
  Serial.println("Trying STA mode."); 
  WiFi.mode(WIFI_STA);  
  WiFi.begin(WIFI_SSID, WIFI_PASS);
   
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    ESP.wdtFeed();       
  } 
  
  if(WiFi.status() == WL_CONNECTED){
    IPAddress stationIP = WiFi.localIP();
    
    String wifi_statusMessage = "Connected to: ";  
    wifi_statusMessage += WIFI_SSID;
    wifi_statusMessage += ". IP address: " + stationIP.toString();  
    
    Serial.println(wifi_statusMessage);
  }
}
