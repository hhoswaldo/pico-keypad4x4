#include "keypad_4x4.h"

#define ROWS 4
#define COLUMNS 4

/* 4x4 Keypad pins */
const int columns[4] = { 18, 19, 20, 21 };
const int rows[4] = {10, 11, 12, 13};

#define GPIO_INPUT false

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
        gpio_set_dir(rows[i], GPIO_INPUT);

        // Enable pull up
        gpio_pull_up(columns[i]);
        gpio_pull_up(rows[i]);
    }
}

char keypad_get_key(void)
{
    // Read all columns when rows active
    // If any column == 0, then key is pressed
    //
    //
    int row;
    uint32_t cols;
    
    for (row = 0; row < 4; row++) {
        for(int j = 0; j < 4; j++) {
            gpio_disable_pulls(rows[j]);
        }
        gpio_pull_up(rows[row]);
        cols = gpio_get_all();
        if (cols != 0x3C0000) {
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        gpio_pull_up(rows[i]);
    }

    if (cols == 0x040000) return row * 4 + 1;
    if (cols == 0x080000) return row * 4 + 2;
    if (cols == 0x100000) return row * 4 + 3;
    if (cols == 0x200000) return row * 4 + 4;
    return 0;
}
