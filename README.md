# ATM Machine Prototype with ATmega32!🏧

This project involves developing a functional ATM prototype capable of performing various operations such as user authentication, balance inquiry, cash withdrawal, and transaction history management. The system features a user-friendly interface with an LCD screen and keypad, all controlled by an ATmega32 microcontroller to ensure secure and efficient operation. The project aims to simulate the essential functions of a real ATM machine.

Key Features:
Microcontroller: ATmega32, providing robust processing and secure operations.
User Interface: Equipped with an LCD screen for displaying information and a keypad for user input.
Functional Operations: Supports balance inquiries, cash withdrawals, cash deposits, and password changes.

Peripherals Used:
ADC (Analog-to-Digital Converter): Integrates sensors, including temperature monitoring with the LM35.
DIO (Digital Input/Output): Manages communication with peripheral devices and user interface components.
EEPROM: Provides non-volatile storage for user data and transaction history.
Timers: Ensures precise control and scheduling within the system.
Interrupts: Handles user actions and system events efficiently and responsively.

Components Used:
LM35: Temperature sensor for monitoring system heat levels.
32.768 kHz Crystal Oscillator: Ensures precise clocking for TIMER2.
Keypad: Allows users to enter PINs and select transactions.
LCD: Displays transaction details, user instructions, and account information.
LEDs and DC Motors: Provide status indicators and manage hardware components.
