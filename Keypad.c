/**
 * 4x4 Keypad Driver Implementation
 */

#include "keypad.h"
#include "delay.h"

// Keypad character mapping
const char keypad_map[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

/**
 * Initialize keypad pins
 */
void keypad_init(void) {
    // Rows as output, Columns as input
    LPC_GPIO2->FIODIR |= KEYPAD_ROW_MASK;
    LPC_GPIO2->FIODIR &= ~KEYPAD_COL_MASK;
    
    // Enable pull-up resistors on column pins
    LPC_PINCON->PINMODE4 &= ~(0xFF << 0);  // Enable pull-up on P2.0-P2.3
    LPC_PINCON->PINMODE4 |= (0x55 << 0);   // Pull-up mode
}

/**
 * Get key press with debouncing
 */
char keypad_get_key(void) {
    static char last_key = 0;
    char current_key = keypad_scan();
    
    if (current_key != 0 && current_key != last_key) {
        last_key = current_key;
        delay_ms(50);  // Debounce delay
        return current_key;
    }
    
    last_key = current_key;
    return 0;
}

/**
 * Scan keypad matrix
 */
char keypad_scan(void) {
    uint8_t row, col;
    
    for (row = 0; row < 4; row++) {
        // Set all rows high
        LPC_GPIO2->FIOSET = KEYPAD_ROW_MASK;
        
        // Set current row low
        LPC_GPIO2->FIOCLR = (1 << (row + 4));
        delay_us(10);  // Small delay for stabilization
        
        // Check each column
        for (col = 0; col < 4; col++) {
            if (!(LPC_GPIO2->FIOPIN & (1 << col))) {
                // Key pressed, wait for release
                while (!(LPC_GPIO2->FIOPIN & (1 << col)));
                delay_ms(50);  // Debounce
                return keypad_map[row][col];
            }
        }
    }
    
    return 0;  // No key pressed
}

/**
 * Check if any key is pressed
 */
uint8_t is_key_pressed(void) {
    for (uint8_t row = 0; row < 4; row++) {
        LPC_GPIO2->FIOSET = KEYPAD_ROW_MASK;
        LPC_GPIO2->FIOCLR = (1 << (row + 4));
        delay_us(10);
        
        for (uint8_t col = 0; col < 4; col++) {
            if (!(LPC_GPIO2->FIOPIN & (1 << col))) {
                return 1;
            }
        }
    }
    return 0;
}
