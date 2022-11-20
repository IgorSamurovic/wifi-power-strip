#include <ESP8266WebServer.h>
#include <pgmspace.h>
#include "http.h"
#include "config.h"
#include "relay.h"

static const char HTML_BEGIN[] PROGMEM = R"(
<!DOCTYPE HTML>
<html>
  <head>
    <meta name = "viewport" content = "width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0">
    <title>Power Strip</title>
    <style>
      .relay_on{color:green;}
      .relay_off{color:red;}
    </style>
  </head>
  <body>
)";

static const char HTML_END[] PROGMEM = "</body></html>";

/* Declaring a web server object. */
static ESP8266WebServer webServer(80);

static void handleRoot(void){
  Serial.println("showStartPage");

  // Check arguments
  String relayIdStr = webServer.arg("id");

  if (relayIdStr != ""){    
    String valueStr = webServer.arg("val");
    
    uint8_t relayId = (uint8_t)relayIdStr.toInt();
    uint8_t value = (uint8_t)valueStr.toInt();

    int result = RELAY_set_id(relayId, value);
    if(result == 0){
      Serial.println("Success");
    }else{
      Serial.println("Fail");
    }
  }

  String forceRefreshApendix = "&time=" + String(millis()); // needed to make url always different to prevent browser caching
  
  String responseStr = FPSTR(HTML_BEGIN);

  for(uint8_t id = 0; id < NUMBER_OF_RELAYS; id++){
    uint8_t relayState = RELAY_getCurrentState(id);
     
    if(relayState == 0){
      responseStr += "<a class='relay_on' href='/?id=" + String(id) + "&val=1" + forceRefreshApendix + "'>Turn Off</a>";
    }else{
      responseStr += "<a class='relay_off' href='/?id=" + String(id) + "&val=0" + forceRefreshApendix + "'>Turn On</a>";
    }

    responseStr += "<br>";
  }

  responseStr += FPSTR(HTML_END);
  webServer.send(200, "text/html", responseStr);  
}


static void handleApi(void){
  // Check arguments
  int result = 1;
  String responseStr = "ERROR: invalid ID";

  // Check arguments
  String relayIdStr = webServer.arg("id");
  
  if (relayIdStr != ""){    
    String valueStr = webServer.arg("val");
    
    uint8_t relayId = (uint8_t)relayIdStr.toInt();
    uint8_t value = (uint8_t)valueStr.toInt();

    result = RELAY_set_id(relayId, value);
    if(result == 0){
      responseStr = "OK";
    }else{
      responseStr = "FAIL";
    }
  }  

  webServer.send(200, "text/plain", responseStr);  
}


static void showNotFound(void){
  webServer.send(404, "text/plain", "Page not found!");      

}

void HTTP_process(void){
  webServer.handleClient(); 
}

void HTTP_init(void){ 
  webServer.on("/", handleRoot);
  webServer.on("/api", handleApi);
  
  webServer.onNotFound([]() {  
     showNotFound();  
  });
  
  webServer.begin();
}
