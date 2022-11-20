#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID "wifi_network_name"
#define WIFI_PASS "my_password"

#define RELAY_1_PIN             (3) 
#define RELAY_2_PIN             (4) 
#define RELAY_3_PIN             (5)
#define RELAY_4_PIN             (12)
#define RELAY_5_PIN             (13)
#define RELAY_6_PIN             (14)

#define NUMBER_OF_RELAYS        (6)

#define SAVED_STATE_ADDR        (0)
#define EEPROM_SIZE             (1)   // using only 1 byte to save 6 bits for relay states


#endif
