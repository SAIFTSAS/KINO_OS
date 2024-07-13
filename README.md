---

# Kino OS

Kino OS is an Arduino-based operating system designed for the Dentaku project by SAIFT S.A.S. It features a graphical user interface (GUI) using an LCD display, keypad input, and various modules for arithmetic operations, gaming, and configuration.

## Features

### Drivers

- **LCD Driver:** Utilizes `LiquidCrystal_I2C` library for interfacing with a 16x2 LCD display.
- **Keypad Driver:** Implements `Keypad` library to handle input from a 4x4 matrix keypad.

### Programmer Control Variables

- **Main Menu:** Initial menu options include "Arimetica", "Videojuego", and "Ajustes".
- **Secondary Menu:** Options under "Arimetica" include "Suma", "Resta", "Multipl", and "Division".
- **Menu Control:** Manages navigation and selection within menus using the LCD display and keypad.

### Arithmetic Logic Unit (ALU)

- **ALU Module:** Supports basic arithmetic operations (addition, subtraction, multiplication, division) and exponentiation.
- **Extended ALU:** Capable of multi-operand calculations for advanced arithmetic scenarios.

### Boot and Control Flow

- **Initialization:** Initializes LCD display, prints "KINO OS", and sets up initial menu display.
- **Main Loop:** Controls the flow of the operating system based on user input and menu selections.
- **Layout Management:** Switches between main menu, secondary menu, arithmetic operations, gaming, and configuration interfaces.

### Configuration and Gaming

- **Configuration Menu:** Placeholder for future configuration options.
- **Game Module:** Simple interactive game with movement and point scoring mechanics.

## Setup and Usage

1. **Hardware Requirements:**
   - Arduino board compatible with `Wire.h`, `LiquidCrystal_I2C.h`, and `Keypad.h` libraries.
   - 16x2 LCD display and a 4x4 matrix keypad.

2. **Software Requirements:**
   - Arduino IDE with necessary libraries installed (`LiquidCrystal_I2C`, `Keypad`).

3. **Installation:**
   - Connect the LCD display and keypad to the Arduino board based on the defined pin configurations (`rowPins`, `colPins`).

4. **Upload Code:**
   - Upload the provided Arduino sketch (`KinoOS.ino`) to your Arduino board using the Arduino IDE.

5. **Usage:**
   - Upon startup, navigate through menus using the keypad (`A` for previous, `B` for next, `*` and `#` for layout changes).
   - Explore arithmetic operations, play the game, or access configuration settings.

## Version and License

- **Version:** 1.1.6
- **Open Source:** This is an open-source version of Kino OS, freely available for modification and distribution.
- **License:** This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## About Dentaku and SAIFT S.A.S.

- **Dentaku:** Kino OS was developed for the Dentaku project, aimed at providing a versatile Arduino-based operating system.
- **SAIFT S.A.S.:** Developed by SAIFT S.A.S., this version of Kino OS is tailored for educational and open-source community use.

## Contributing

Contributions to Kino OS are welcome! Feel free to submit bug reports, feature requests, or pull requests via GitHub Issues.

---
