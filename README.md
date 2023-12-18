# NintendoSwitchControlLibrary

A library for microcontrollers that automates Nintendo Switch games using Arduino.

![demo](https://user-images.githubusercontent.com/49473970/107502281-d0cc6c80-6bdb-11eb-9928-fb0a29744df6.gif)

## ⭐ About this Library

This library is based on [SwitchControlLibrary](https://github.com/celclow/SwitchControlLibrary) by celclow.

Although [SwitchControlLibrary](https://github.com/celclow/SwitchControlLibrary) offers a high degree of freedom, its main problem was that the code tends to be redundant and that it takes time to compile because it uses ArduinoSTL.

So, we decided to carefully select commonly used input patterns and summarize them in a function.

The process of pressing and releasing a button can now be written on a single line, allowing for more efficient automation programs. The program can also be used for mashing or holding a button, making it a highly versatile program.

Most importantly, we have succeeded in implementing these processes without using the ArduinoSTL. This allows for faster compilation and also eliminates the need to worry about dependencies.

## 🔹 Introduction

### Requirements

- Arduino Leonardo
- USB cable (required to connect Arduino Leonardo to Switch or PC)

### Programming Environment

- Arduino IDE (1.8.13 recommended)
- Arduino AVR Boards (1.8.3 recommended)

For detailed installation instructions, please refer to our blog post (Translator's note - Blog post has yet to be translated):

[Use a Microcontroller to Automate Pokémon Sword and Shield! \[Mac/Windows\] | Pokémonit ](https://pokemonit.com/micon-introduction/)

## ⚠️ Important Notes

We recommend you use the Arduino Leonardo linked in the blog post. We have not tested the operation of any other Arduino boards. If you use a different one, we will not be able to answer any questions.

The Arduino IDE and board versions are basically the latest stable versions that have been tested to work. Older versions may be usable, but we do not guarantee their operation.

Note that there is no specification for the Nintendo Switch firmware version. Any version above 3.0.0 should work without problems.

## 📄 Usage

Please put the following at the beginning of the file in which you want to use the library:

```
#include <NintendoSwitchControlLibrary.h>
```

This will allow you to load the libraries and use the commands you want.

Since this is a standalone library, there is no need to load separate libraries such as ArduinoSTL or [SwitchControlLibrary](https://github.com/celclow/SwitchControlLibrary).

**[SwitchControlLibrary](https://github.com/celclow/SwitchControlLibrary) cannot be used simultaneously with this because of conflicts with said program.** However, since NintendoSwitchControlLibrary inherits commands from [SwitchControlLibrary](https://github.com/celclow/SwitchControlLibrary) (v2), it is possible to use commands from SwitchControlLibrary as well. (Because we aren't using ArduinoSTL, the D-Pad commands work a little differently, but they can be used in basically the same way.)

## ⌨️ List of commands

### Button

- Command to press a button (also supports consecutive presses)

  - `pushButton(uint16_t button, int delay_time = 0, int loop = 1)`

    - button: button to push
    - delay_time: Delay time after pressing the button (1 second = 1000) 
    - loop: Number of button presses (optional, default is 1)

  - Examples

    ```
    pushButton(Button::HOME);        // Press the HOME button
    pushButton(Button::A, 500);      // Wait 0.5 seconds after pressing A
    pushButton(Button::B, 3000, 10); // Press the B button every 3 seconds, repeat 10 times.
    ```

- Command to press and hold the button.

  - `holdButton(uint16_t button, int hold_time)`

    - button: Button to be held
    - hold_time: Amount of time to hold the button for (1 second = 1000)

  - Examples

    ```
    holdButton(Button::L, 2000);       // Hold the L button for 2 seconds
    holdButton(Button::CAPTURE, 1500); // Hold the screenshot button for 1.5 seconds
    ```

- `Button` Definition List

  ```
  Button::Y
  Button::B
  Button::A
  Button::X
  Button::L
  Button::R
  Button::ZL
  Button::ZR
  Button::MINUS
  Button::PLUS
  Button::LCLICK
  Button::RCLICK
  Button::HOME
  Button::CAPTURE
  ```

### D-Pad

- Commands to push a button on the D-Pad (Also supports consecutive presses)

  - `pushHat(uint8_t hat, int delay_time = 0, int loop = 1);`

    - hat: D-Pad button to press
    - delay_time: Delay time after pressing the button (1 second = 1000)
    - loop: Number of button presses (optional, default is 1)

  - Examples

    ```
    pushHat(Hat::UP);          // Press up once
    pushHat(Hat::LEFT, 1000);  // Press left and wait 1 second.
    pushHat(Hat::DOWN, 25, 5); // Press down every 0.25 seconds, repeat 5 times.
    ```

- Commands to hold a button on the D-Pad

  - `holdHat(uint8_t hat, int hold_time);`

    - hat: D-Pad button to hold
    - hold_time: Amount of time to hold the button for (1 second = 1000)

  - Examples

    ```
    holdHat(Hat::RIGHT, 5000);   // Hold right on the D-Pad for 5 seconds
    holdHat(Hat::UP_LEFT, 2500); // Hold up and left on the D-Pad for 2.5 seconds
    ```

- `Hat` Definition List

  ```
  Hat::UP
  Hat::UP_RIGHT
  Hat::RIGHT
  Hat::DOWN_RIGHT
  Hat::DOWN
  Hat::DOWN_LEFT
  Hat::LEFT
  Hat::UP_LEFT
  Hat::NEUTRAL
  ```

### Stick

The coordinates of the stick are specified as a value from 0 to 255 with 128 as the neutral point.

The three values 0, 128, and 255 are defined in Stick and can be used interchangeably (0 = MIN, NEUTRAL = 128, MAX = 255).

In addition, by passing buttons as an argument, it is possible to perform the operation of tilting the stick while repeatedly hitting the buttons.

- Commands to control the left stick

  - `tiltLeftStick(uint8_t lx, uint8_t ly, int tilt_time, uint16_t button = NULL);`

    - lx: Left stick X-axis
    - ly: Left stick Y-axis
    - tilt_time: Amount of time to tilt the stick for
    - button: Buttons to press repeatedly

  - Examples

    ```
    tiltLeftStick(0, 128, 5000);                                // Tilt the left stick to the left for 5 seconds
    tiltLeftStick(Stick::NEUTRAL, Stick::MAX, 15000);           // Tilt the left stick down for 15 seconds
    tiltLeftStick(Stick::NEUTRAL, Stick::MIN, 8000, Button::A); // Tilt the left stick up for 8 seconds while mashing A
    ```

- Commands to control the right stick

  - `tiltRightStick(uint8_t rx, uint8_t ry, int tilt_time, uint16_t button = NULL);`

    - rx: Right stick X-axis
    - ry: Right stick Y-axis
    - tilt_time: Amount of time to tilt the stick for
    - button: buttons to press repeatedly

  - Examples

    ```
    tiltRightStick(255, 128, 100);                                 // Tilt right stick to the right for 0.1 seconds
    tiltRightStick(Stick::MAX, Stick::MIN, 10000);                 // Tilt right stick to the top right for 10 seconds
    tiltRightStick(Stick::NEUTRAL, Stick::MAX, 30000, Button::X);  // Hold the right stick down for 30 seconds while mashing X
    ```

- Commands to move the left and right sticks simultaneously

  - `tiltLeftAndRightStick(uint8_t lx, uint8_t ly, uint8_t rx, uint8_t ry, int tilt_time, uint16_t button = NULL);`

    - lx: Left stick X-axis
    - ly: Left stick Y-axis
    - rx: Right stick X-axis
    - ry: Right stick Y-axis
    - tilt_time: Amount of time to tilt the stick for
    - button: Button to press repeatedly

  - Examples

    ```
    tiltLeftAndRightStick(128, 255, 0, 128, 1000);                                                // Tilt the left stick down and the right stick left for 1 second
    tiltLeftAndRightStick(Stick::MAX, Stick::MAX, Stick::MIN, Stick::MIN, 30000);                 // Tilt the left stick to the bottom-right and the right stick to the top-left for 30 seconds
    tiltLeftAndRightStick(Stick::NEUTRAL, Stick::MAX, Stick::MIN, Stick::MAX, 2000, Button::B);   // While mashing B, tilt the left stick down and the right stick to the bottom-left for 2 seconds
    ```

- `Stick` Definition List

  ```
  Stick::MIN
  Stick::NEUTRAL
  Stick::MAX
  ```

### Spinning a Stick

- Commands to spin the left stick

  - `spinLeftStick(int spin_time, uint8_t speed = 5, bool direction = 1);`

    - spin_time: Amount of time to spin the stick (any fractional time that takes less than one spin will be rounded down)
    - speed: Number of spins per second
    - direction: Direction to spin (1: clockwise; 0: counterclockwise)

  - Examples

    ```
    spinLeftStick(10000);       // Spin the left stick clockwise for 10 seconds at a rate of 5 spins per second
    spinLeftStick(30000, 1);    // Spin the left stick clockwise for 30 seconds at a rate of 1 spin per second
    spinLeftStick(25000, 3, 0); // Spin the left stick counterclockwise for 25 seconds at a rate of 3 times per second
    ```

- Commands to spin the left stick

  - `spinRightStick(int spin_time, uint8_t speed = 5, bool direction = 1);`

    - spin_time: Amount of time to spin the stick (any fractional time that takes less than one spin will be rounded down)
    - speed: Number of spins per second
    - direction: Direction to spin (1: clockwise; 0: counterclockwise)

  - Examples

    ```
    spinRightStick(5000);        // Spin the right stick clockwise for 5 seconds at a rate of 5 times per second
    spinRightStick(9000, 10, 0); // Spin the right stick counterclockwise for 9 seconds at a rate of 10 times per second
    spinRightStick(3000, 4, 1);  // Spin the right stick clockwise for 3 seconds at a rate of 4 times per second
    ```

### More commands from SwitchControlLibrary

This library also has SwitchControlLibrary commands built in, so they can be used together. (Note: This library uses the v2 version, so it is not compatible with v1 commands.)

If there is something that isn't explained above, you can make use of it.

As a sample, we have made a script to load save data from Pokémon Sword and Shield.

```
SwitchControlLibrary().pressButton(Button::B);
SwitchControlLibrary().pressButton(Button::X);
SwitchControlLibrary().pressHatButton(Hat::UP); // *Unlike SwitchControlLibrary, moveHat no longer works. It is integrated into pressHatButton.
SwitchControlLibrary().sendReport();            // B, X, and UP buttons are sent at the same time
delay(100);
SwitchControlLibrary().releaseButton(Button::B);
SwitchControlLibrary().releaseButton(Button::X);
SwitchControlLibrary().releaseHatButton();      // *Unlike SwitchControLibrary, no argument is specified. (This process returns the D-Pad to the neutral position.)
SwitchControlLibrary().sendReport();            // Release B, X, and UP buttons simultaneously
```

## 🎁 Conclusion

This library is tentative, so if you have any requests or, suggestions for improvement, or features you would like to see added, please feel free to send them in via [Issues](https://github.com/lefmarna/NintendoSwitchControlLibrary/issues).

It may be difficult to create something as advanced as image recognition, but I think this can handle the range of uses for input programs.

## ©️ License

[MIT](https://github.com/lefmarna/NintendoSwitchControlLibrary/blob/master/LICENSE)
