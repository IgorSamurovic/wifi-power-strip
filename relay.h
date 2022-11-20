#ifndef RELAY_H
#define RELAY_H

int RELAY_set_id( uint8_t relay_id, uint8_t value);
void RELAY_set_all( uint8_t value);
void RELAY_init(void);
uint8_t RELAY_getCurrentState(uint8_t relay_id);

#endif
