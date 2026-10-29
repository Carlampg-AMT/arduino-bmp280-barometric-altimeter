# Arduino-Based Barometric Altimeter Using BMP280

An educational aviation electronics project that uses an Arduino Uno and a BMP280 barometric pressure sensor to measure atmospheric pressure and estimate altitude. The readings are displayed on a 16x2 I2C LCD, while a rotary encoder allows manual adjustment of the QNH setting.

This project was developed as a hands-on learning activity to explore barometric altitude measurement, atmospheric pressure, sensor interfacing, and embedded systems programming.

## Features

- Atmospheric pressure measurement using the BMP280 sensor
- Barometric altitude estimation
- Real-time readings displayed on a 16x2 I2C LCD
- Manual QNH adjustment using a rotary encoder
- Temperature measurement using the BMP280
- Arduino-based hardware and software integration

## Hardware Components

- Arduino Uno
- BMP280 barometric pressure sensor
- 16x2 LCD with I2C interface
- KY-040 rotary encoder
- Jumper wires
- Breadboard and connecting materials
- 3D-printed enclosure

## Software and Libraries

- Arduino IDE
- Adafruit BMP280 Library
- Adafruit Unified Sensor Library
- LiquidCrystal I2C Library

## How It Works

The BMP280 sensor measures atmospheric pressure and temperature. The Arduino processes the sensor readings and estimates altitude based on the pressure measurement and the selected reference pressure.

The LCD displays the measured values, while the rotary encoder allows the user to adjust the QNH reference setting.

## QNH and Altitude

QNH is the pressure setting used to reference an altimeter to mean sea level. Changing the QNH setting affects the calculated indicated altitude even when the sensor remains at the same physical location.

The displayed altitude is an estimate based on barometric pressure and the selected reference setting. Atmospheric pressure changes due to weather and other conditions can affect the reading.

## Project Purpose

The purpose of this project is to demonstrate the basic principles of barometric altitude measurement and the integration of electronic sensors with a microcontroller.

It also provides practical experience in Arduino programming, electronic circuit assembly, troubleshooting, and prototype development.

## Limitations

- This is an educational prototype and not a certified aviation instrument.
- Altitude accuracy depends on sensor calibration, reference pressure, and atmospheric conditions.
- Temperature readings may differ from those of a weather station because of sensor placement and environmental conditions.
- The device should not be used for actual aircraft navigation or flight operations.

## Future Improvements

- Improve altitude calibration and stability.
- Add a more accurate reference-pressure adjustment process.
- Implement data logging.
- Improve the enclosure and sensor protection.
- Compare measurements with a known reference altimeter.

## Author

Carl Ampong 

Associate in Aircraft Maintenance Technology Student

## License

This project is shared for educational and personal learning purposes. See the LICENSE file for the applicable terms.
