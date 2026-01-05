/**
 * LCD Driver Implementation
 */

#include "lcd.h"
#include "delay.h"

/**
 * Initialize LCD in 4-bit mode
 */
void lcd_init(void) {
    // Configure pins as output
    LPC_GPIO0->FIODIR |= LCD_RS | LCD_EN | LCD_DATA_MASK;
    
    delay_ms(20);  // Wait for LCD power up
    
    // Initialize in 4-bit mode
    lcd_cmd_write(0x33);
    lcd_cmd_write(0x32);
    lcd_cmd_write(0x28);  // 4-bit, 2-line, 5x8 font
    lcd_cmd_write(0x0C);  // Display on, cursor off
    lcd_cmd_write(0x06);  // Entry mode
    lcd_cmd_write(0x01);  // Clear display
    delay_ms(2);
}

/**
 * Send command to LCD
 */
void lcd_cmd_write(uint8_t cmd) {
    // Send higher nibble
    LPC_GPIO0->FIOCLR = LCD_DATA_MASK;
    LPC_GPIO0->FIOSET = ((cmd & 0xF0) << 11);  // Shift for P0.15-P0.18
    
    LPC_GPIO0->FIOCLR = LCD_RS;  // RS=0 for command
    LPC_GPIO0->FIOSET = LCD_EN;  // Enable high
    delay_us(1);
    LPC_GPIO0->FIOCLR = LCD_EN;  // Enable low
    delay_us(100);
    
    // Send lower nibble
    LPC_GPIO0->FIOCLR = LCD_DATA_MASK;
    LPC_GPIO0->FIOSET = ((cmd & 0x0F) << 15);  // Shift for P0.15-P0.18
    
    LPC_GPIO0->FIOSET = LCD_EN;  // Enable high
    delay_us(1);
    LPC_GPIO0->FIOCLR = LCD_EN;  // Enable low
    delay_us(100);
}

/**
 * Send data to LCD
 */
void lcd_data_write(uint8_t data) {
    // Send higher nibble
    LPC_GPIO0->FIOCLR = LCD_DATA_MASK;
    LPC_GPIO0->FIOSET = ((data & 0xF0) << 11);
    
    LPC_GPIO0->FIOSET = LCD_RS;  // RS=1 for data
    LPC_GPIO0->FIOSET = LCD_EN;  // Enable high
    delay_us(1);
    LPC_GPIO0->FIOCLR = LCD_EN;  // Enable low
    delay_us(100);
    
    // Send lower nibble
    LPC_GPIO0->FIOCLR = LCD_DATA_MASK;
    LPC_GPIO0->FIOSET = ((data & 0x0F) << 15);
    
    LPC_GPIO0->FIOSET = LCD_EN;
    delay_us(1);
    LPC_GPIO0->FIOCLR = LCD_EN;
    delay_us(100);
}

/**
 * Write string to LCD
 */
void lcd_str_write(const char *str) {
    while (*str) {
        lcd_data_write(*str++);
    }
}

/**
 * Set cursor position
 */
void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t address;
    
    if (row == 0) {
        address = 0x80 + col;  // First line
    } else {
        address = 0xC0 + col;  // Second line
    }
    
    lcd_cmd_write(address);
}

/**
 * Clear LCD display
 */
void lcd_clear(void) {
    lcd_cmd_write(LCD_CLEAR);
    delay_ms(2);
}
