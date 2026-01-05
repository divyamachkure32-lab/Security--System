# Password Security System using LPC1768

## Project Overview
A secure password-based access control system implemented on LPC1768 ARM Cortex-M3 microcontroller with 4x4 keypad, LCD display, and buzzer feedback.

## Features
- 4-digit password protection
- LCD display for user interface
- Audio feedback using buzzer
- Keypad input for password entry
- Configurable password storage
- Error handling and timeout mechanisms

## Hardware Requirements
- LPC1768 Development Board
- 16x2 LCD Display (HD44780 compatible)
- 4x4 Matrix Keypad
- Buzzer
- Connecting wires
- Power supply (3.3V)

## Hardware Connections

### LCD Connections (Port 0):
- RS  → P0.10
- EN  → P0.11
- D4  → P0.15
- D5  → P0.16
- D6  → P0.17
- D7  → P0.18

### Keypad Connections (Port 2):
- Rows: P2.4 - P2.7
- Columns: P2.0 - P2.3

### Buzzer:
- Signal → P0.10

## Software Requirements
- Keil uVision 5
- CMSIS Core for Cortex-M3
- LPC17xx Device Family Pack

## Building the Project
1. Open `project/PasswordSecuritySystem.uvprojx` in Keil uVision
2. Build the project (F7)
3. Connect LPC1768 via USB
4. Flash the binary file

## Usage
1. System boots and displays "Enter Password:"
2. Enter 4-digit password using keypad
3. LCD shows '*' for each entered digit
4. Press '#' to confirm or '*' to clear
5. Correct password: "Valid Password" + short beep
6. Wrong password: "Invalid Password" + long beep

## Default Password
- Default password: "1914"
- Can be changed in `system_config.h`
