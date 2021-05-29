/*
||
|| @file keypad_4x4.c
|| @version 0.1
|| @author Oswaldo Hernandez, Owen Jauregui
|| @contact oswahdez00@gmail.com
||
|| @description
|| | This library provides a simple interface for using matrix
|| | keypads on the Raspberry Pico.
*/

#include "keypad_4x4.h"

#define ROWS 4
#define COLUMNS 4

#define GPIO_INPUT false
#define GPIO_OUTPUT true

/* 4x4 Keypad pins */
const uint columns[4] = { 18, 19, 20, 21 };
const uint rows[4] = { 10, 11, 12, 13 };
const char matriz[16] = { '1', '2' , '3', 'A',
                          '4', '5' , '6', 'B',
                          '7', '8' , '9', 'C',
                          '*', '0' , '#', 'D'};

void keypad_init(void)
{
    /* Initialize GPIO function pins */
    for (int i = 0; i < 4; i++)
    {
        /* Initialize GPIOs */
        gpio_init(columns[i]);
        gpio_init(rows[i]);

        /* Set GPIOs as inputs */
        gpio_set_dir(columns[i], GPIO_INPUT);
        gpio_set_dir(rows[i], GPIO_OUTPUT);

        gpio_put(rows[i], 1);       /* Assign value to 1 */
    }
}

char keypad_get_key(void)
{
    int row;
    uint32_t cols;
    bool pressed = false;
    
    cols = gpio_get_all();
    cols = cols & 0x3C0000;
    if (cols == 0x0) {
        return 0;
    }
    
    for (int j = 0; j < 4; j++) {
        gpio_put(rows[j], 0);
    }

    for (row = 0; row < 4; row++) {
    
        gpio_put(rows[row], 1);

        sleep_ms(10);

        cols = gpio_get_all();
        gpio_put(rows[row], 0);
        cols = cols & 0x3C0000;
        if (cols != 0x0) {
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        gpio_put(rows[i], 1);
    }

    if (cols == 0x040000) return (char) matriz[row * 4 + 0];
    if (cols == 0x080000) return (char) matriz[row * 4 + 1];
    if (cols == 0x100000) return (char) matriz[row * 4 + 2];
    if (cols == 0x200000) return (char) matriz[row * 4 + 3];
    return 0;
}
