#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include "pico/stdlib.h"
#include "hardware/timer.h"

void keypad_init(void);

char keypad_get_key(void);

void keypad_irq_enable(bool enable, gpio_irq_callback_t callback);

#endif