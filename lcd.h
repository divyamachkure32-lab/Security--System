/**
 * LCD Driver Header File
 * HD44780 compatible 16x2 LCD
 */

#ifndef LCD_H
#define LCD_H

#include "LPC17xx.h"
#include <stdint.h>

// Pin Definitions
#define LCD_RS (1 << 10)  // P0.10
#define LCD_EN (1 << 11)  // P0.11
#define LCD_DATA_MASK (0xFF << 15)  // P0.15-P0.22

// LCD Commands
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_ENTRY_MODE 0x06
#define LCD_DISPLAY_OFF 0x08
#define LCD_DISPLAY_ON 0x0C
#define LCD_CURSOR_ON 0x0E
#define LCD_CURSOR_BLINK 0x0F
#define LCD_CURSOR_OFF 0x0C
#define LCD_FUNCTION_SET 0x38

// Function Prototypes
void lcd_init(void);
void lcd_cmd_write(uint8_t cmd);
void lcd_data_write(uint8_t data);
void lcd_str_write(const char *str);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_clear(void);

#endif // LCD_H
