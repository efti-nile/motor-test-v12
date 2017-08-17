#include "main.h"

int main(void) {
  uint8_t is_btn_pushed = 0, is_overload = 0;
  
  motor_init();
  
  while (1) {
    // Detecting button trailing edge
    if (debounced_poll(&BTN_PIN, 1 << BTN_PIN_NO, NOT_INV)) {
      is_btn_pushed = 1;
    }
    if (is_btn_pushed && debounced_poll(&BTN_PIN, 1 << BTN_PIN_NO, INV)) {
      is_btn_pushed = 0;
      motor_togle();
    }
    
    // Detecting overload leading edge
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
