#include "motor.h"

static uint8_t dir = 0; // Rotation direction

void motor_init(void) {
  // Config motor pins as output
  MOTOR_FWD_DDR |= 1 << MOTOR_FWD_PIN_NO;
  MOTOR_BWD_DDR |= 1 << MOTOR_BWD_PIN_NO;
  
  motor_stop();
  
  dir = 0;
}

void motor_togle(void) {
  if (dir & 1) {
    MOTOR_FWD_PORT ^= 1 << MOTOR_FWD_PIN_NO;
  } else {
    MOTOR_BWD_PORT ^= 1 << MOTOR_BWD_PIN_NO;
  }
}

void motor_start(void) {
  if (dir & 1) {
    MOTOR_BWD_PORT |= 1 << MOTOR_BWD_PIN_NO;
  } else {
    MOTOR_FWD_PORT |= 1 << MOTOR_FWD_PIN_NO;
  }
}

void motor_stop(void) {
  MOTOR_FWD_PORT &= ~(1 << MOTOR_FWD_PIN_NO);
  MOTOR_BWD_PORT &= ~(1 << MOTOR_BWD_PIN_NO);
}

void motor_reverse(void) {
  if ((dir & 1) && (MOTOR_FWD_PORT & 1 << MOTOR_FWD_PIN_NO)) {
    MOTOR_FWD_PORT &= ~(1 << MOTOR_FWD_PIN_NO);
    _delay_ms(5);
    MOTOR_BWD_PORT |= 1 << MOTOR_BWD_PIN_NO;
  }
  if (!(dir & 1) && (MOTOR_BWD_PORT & 1 << MOTOR_BWD_PIN_NO)) {
    MOTOR_BWD_PORT &= ~(1 << MOTOR_BWD_PIN_NO);
    _delay_ms(5);
    MOTOR_FWD_PORT |= 1 << MOTOR_FWD_PIN_NO;
  }
  ++dir;
}
