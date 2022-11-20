# Power Control

This Arduino sketch is using **ESP8266** WiFi module and relays to controll 6 power outlets.
It provides a web interface, so you can connect to it using any web enabled device.

To keep things simple, the WiFi credentials and used pins are hard-coded, so you will need to edit the config.h before flashing.

## How to start

To add support for ESP8266 in Arduino IDE, click on "File > Preferences" and in the 'Additional boards manager" input field add 
"http://arduino.esp8266.com/stable/package_esp8266com_index.json"

If there already is any configuration, you may add a comma and then this text.

We will be using some additional libraries so you need to add them to the Arduino IDE. Open "Sketch > Include Library > Manage Libraries" and add "ESP_EEPROM"

## Usage

To view the basic web page, go to the IP address and root page and use the links to turn relays on/off.
To controll the device via API, use the "/api" page with parameters like:

    192.168.0.100/api?id=<relayId>&val=<1/0>
