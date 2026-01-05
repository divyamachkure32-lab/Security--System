/**
 * 4x4 Keypad Driver Header
 */

#ifndef KEYPAD_H
#define KEYPAD_H

#include "LPC17xx.h"
#include <stdint.h>

// Keypad Pin Definitions (Port 2)
#define KEYPAD_ROW_MASK (0x0F << 4)  // P2.4-P2.7
#define KEYPAD_COL_MASK (0x0F << 0)  // P2.0-P2.3

// Keypad mapping
extern const char keypad_map[4][4];

// Function Prototypes
void keypad_init(void);
char keypad_get_key(void);
char keypad_scan(void);
uint8_t is_key_pressed(void);

#endif // KEYPAD_H
