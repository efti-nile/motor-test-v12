#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#define MOTOR_FWD_DDR     DDRC
#define MOTOR_FWD_PORT    PORTC
#define MOTOR_FWD_PIN_NO  0

#define MOTOR_BWD_DDR     DDRC
#define MOTOR_BWD_PORT    PORTC
#define MOTOR_BWD_PIN_NO  1

void motor_init(void);
void motor_togle(void);
void motor_start(void); 
void motor_stop(void);
void motor_reverse(void);

#endif