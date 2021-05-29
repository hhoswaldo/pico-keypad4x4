#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include "pico/stdlib.h"

void keypad_init(void);
char keypad_get_key(void);

#endif