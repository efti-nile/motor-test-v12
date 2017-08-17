#include "main.h"

int main(void) {
  uint8_t is_btn_pushed = 0, is_overload = 0;
  
  _delay_ms(1000);
  
  asm("WDR\n");
  
  // Config motor pins as output
  MOTOR_FWD_DDR |= 1 << MOTOR_FWD_PIN_NO;
  MOTOR_BWD_DDR |= 1 << MOTOR_BWD_PIN_NO;
  
  MOTOR_FWD_PORT |= 1 << MOTOR_FWD_PIN_NO; // Start motor
  
  while (1) {
    // Detect button trailing edge
    if (debounced_poll(&BTN_PIN, 1 << BTN_PIN_NO, NOT_INV)) {
      is_btn_pushed = 1;
    }
    if (is_btn_pushed && debounced_poll(&BTN_PIN, 1 << BTN_PIN_NO, INV)) {
      motor_reverse();
      is_btn_pushed = 0;
    }
    
    // Detect overload leading edge
    if (!is_overload && debounced_poll(&OVLD_PIN, 1 << OVLD_PIN_NO, NOT_INV)) {
      motor_reverse();
      is_overload = 1;
      _delay_ms(500);
    }
    if (debounced_poll(&OVLD_PIN, 1 << OVLD_PIN_NO, INV)) {
      is_overload = 0;
    }
    
    asm("WDR\n");
  }
  
  return 0;
}

uint8_t debounced_poll(volatile uint8_t *p, uint8_t m, uint8_t inv) {
  uint16_t t = 0x0000;
  while ((*p ^ inv) & m) {
    if (++t >= 0xFFFF) {
      return 1;
    }
  }
  return 0;
}

void motor_reverse(void) {
  if (MOTOR_FWD_PORT & 1 << MOTOR_FWD_PIN_NO) {
    MOTOR_FWD_PORT ^= 1 << MOTOR_FWD_PIN_NO;
    _delay_ms(5);
    MOTOR_BWD_PORT |= 1 << MOTOR_BWD_PIN_NO;
  } else if (MOTOR_BWD_PORT & 1 << MOTOR_BWD_PIN_NO) {
    MOTOR_BWD_PORT ^= 1 << MOTOR_BWD_PIN_NO;
    _delay_ms(5);
    MOTOR_FWD_PORT |= 1 << MOTOR_FWD_PIN_NO;
  }
}
