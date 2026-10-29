# Required Libraries

This project uses the Arduino Uno, BMP280 barometric pressure sensor, 16x2 I2C LCD, and KY-040-compatible rotary encoder wiring.

## Required Arduino Libraries

Install the following libraries using the Arduino IDE Library Manager.

| Library | Purpose |
|---|---|
| Adafruit BMP280 Library | Reads atmospheric pressure and temperature from the BMP280 sensor. |
| Adafruit Unified Sensor | Provides the sensor abstraction used by Adafruit sensor libraries. |
| LiquidCrystal I2C | Controls the 16x2 I2C LCD. |

## Built-in Libraries

These libraries are included with the Arduino environment and do not normally require separate installation.

- `Wire.h` — I2C communication.
- `math.h` — Mathematical functions, including `pow()`.

## Installation Instructions

1. Open the Arduino IDE.
2. Go to **Sketch → Include Library → Manage Libraries**.
3. Search for `Adafruit BMP280 Library` and install it.
4. Install `Adafruit Unified Sensor` if prompted or if it is not already installed.
5. Search for `LiquidCrystal I2C` and install a compatible library.
6. Open `altimeter.ino`, select Arduino Uno as the board, and compile the sketch.

## Notes

- The LCD library must support the `LiquidCrystal_I2C` interface used by the source code.
- The LCD I2C address in this project is `0x27`.
- The BMP280 sensor is initialized using address `0x76`, with `0x77` as a fallback.
- The rotary encoder is read directly through Arduino digital pins, so a separate rotary encoder library is not required.

## Compatibility

Library APIs and LCD implementations may differ between versions. If compilation fails, check the installed library and its compatibility with the source code.
