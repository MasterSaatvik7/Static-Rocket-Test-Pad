# SPIDER STATIC TEST PAD

## Overview

The SPIDER STATIC TEST PAD is a quadruped static rocket motor testing platform designed for performance analysis of high-powered rocket motors. It enables standardized and accurate thrust testing for motors up to N-class or motors with dimensions ranging from 3 cm to 16 cm in diameter and up to 70 cm in length.

This project was developed during an internship at STAR – Space Technology and Aeronautical Rocketry and focuses on testing rocket motors producing thrust up to 3000 N while capturing thrust-time and temperature-time characteristics.

## Features

- **Thrust Measurement**: HX711 load cell measures thrust up to 300 kg.
- **Temperature Monitoring**: MAX31855 thermocouple measures motor surface temperatures up to 1400 °C.
- **Data Storage**: Observations are recorded and stored using an Arduino SD card module.
- **Sturdy and Lightweight Design**: Built with carbon fiber, magnesium alloy, and neoprene for high strength, low weight, and reduced vibrations.
- **Simulation Verified**: Transient structural, strain, stress, safety factor, and thermal analyses confirm operational safety.

## Components

### Hardware

1. **Motor Mount**: Carbon fiber, lightweight and strong.
2. **Clamps**: Stainless steel with ball bearings for stability and axial motion.
3. **Legs**: Magnesium alloy for strength and reduced weight.
4. **Sensors**:
   - HX711 load cell for thrust measurement.
   - MAX31855 thermocouple for temperature measurement.
5. **Avionics Box**: Houses the Arduino and additional components.
6. **Miscellaneous**: Rubber pads (vibration dampening), aluminum screws, and an ignition wire.

### Electronics

- Arduino UNO microcontroller
- SD card module
- Resistors, capacitors, transistors
- TO-220 NPN current amplifier
- 11V LiPo battery

### Software

- **Arduino IDE**: Programming and uploading Arduino code.
- **Fusion 360 / Ansys**: CAD design and structural analysis.
- **Proteus / EasyEDA / Eagle**: Circuit design and PCB fabrication.

## Assembly Instructions

### Avionics

1. Select components (Arduino UNO, load cell, thermocouple, etc.).
2. Connect components per the schematic.
3. Fabricate a PCB based on the schematic and mount components.

### Mechanical Structure

1. Assemble the motor mount and attach clamps.
2. Fix thermocouples to the motor surface.
3. Attach legs to the motor mount.
4. Connect all sensors to the avionics box.

## Arduino Code Description
The Arduino code governs the core functionalities of the SPIDER STATIC TEST PAD, integrating the sensors, data recording, and ignition control:

1. **Thrust Measurement**: Utilizes the HX711 load cell to capture thrust data in real time and records it to an SD card.
2. **Temperature Monitoring**: Reads data from two MAX31855 thermocouples to monitor motor surface temperatures during tests.
3. **Ignition System**: Activates the ignition system after a safety delay using a digital pin.
4. **Data Logging**: Writes both thrust and temperature data to separate files (`TEST_DATA.txt` and `TEST_Temp_DATA.txt`) on the SD card for later analysis.
5. **Error Handling**: Includes fault detection for thermocouples, ensuring operational safety during tests.

The code initializes all sensors, calibrates the load cell, and ensures all data is captured efficiently during tests. Detailed serial outputs assist in debugging and monitoring test conditions.

## Simulations and Results

1. **Structural Analysis**:
   - Maximum deformation: 0.96793 mm.
   - Maximum stress: 575.18 MPa.
   - Safety factor: Minimum 0.34554.
2. **Thermal Analysis**:
   - Maximum temperature: 1406.3 °C.
   - Maximum heat flux: 1.4385 W/mm².
3. The design withstands forces up to 3000 N for 20 seconds and temperatures up to 1400 °C.

## Precautions

- Ensure the motor is securely clamped.
- Test on a leveled surface.
- Maintain a safe distance during operation.
- Additional testing and troubleshooting may be required post-manufacturing.

## Product Specifications

- **Weight**: 16 kg
- **Height**: 50 cm
- **Base Area**: 0.320 m²
- **Cost**: ₹17,000

## Acknowledgments

This is a Static Rocket Motor Test Pad developed by me and my team under STAR LABS, Surat. The test pad design in Fusion 360 and Ansys was contributed by Vikrant, and the avionics box design was led by Dattasai. The Arduino code was collaboratively implemented and tested by the team. The project was guided by STAR LAB mentors and would not have been possible without their support and encouragement.

## Future Work

- Finalize the design and manufacture the test pad.
- Validate performance with real-world tests.
- Implement advanced data visualization and analytics.

---

