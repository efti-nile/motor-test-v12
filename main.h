#ifndef MAIN_H
#define MAIN_H_

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#define BTN_DDR       DDRD
#define BTN_PIN       PIND
#define BTN_PIN_NO    5

#define OVLD_DDR      DDRD
#define OVLD_PIN      PIND
#define OVLD_PIN_NO   0

#define MOTOR_FWD_DDR     DDRC
#define MOTOR_FWD_PORT    PORTC
#define MOTOR_FWD_PIN_NO  0

#define MOTOR_BWD_DDR     DDRC
#define MOTOR_BWD_PORT    PORTC
#define MOTOR_BWD_PIN_NO  1

#define INV     0xFF
#define NOT_INV 0x00

uint8_t debounced_poll(volatile uint8_t *p, uint8_t m, uint8_t inv);
void motor_reverse(void);

#endif
