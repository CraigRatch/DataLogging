# DataLogging
Arduino SD card read/write example for future datalogging
# Arduino SD Card and GPS Logger Projects
**Author:** Craig Ratchford

## Overview
This repository contains two Arduino projects demonstrating SD card usage:

1. **SD Card Test** – A simple example writing and reading numbers from a file on an SD card.
2. **GPS Data Logger** – Reads GPS coordinates from an Adafruit GPS module and logs them to an SD card with timestamps.

These projects are useful for learning **file handling**, **data logging**, and **basic GPS integration** with Arduino.

---

## Project 1: SD Card Test

### Description
This program writes numbers 0–5 to a file on an SD card and reads them back, displaying the results on the Serial Monitor. It demonstrates basic SD card initialization, file creation, writing, and reading.

### Hardware Required
- Arduino (Uno, Mega, etc.)
- SD Card Module
- SD Card (FAT16/FAT32)
- Jumper wires

### Pin Configuration
| Component     | Arduino Pin |
|---------------|-------------|
| SD Card CS    | 9           |
| SPI Pins      | 11 (MOSI), 12 (MISO), 13 (SCK) |
| Pin 10        | OUTPUT (required by SD library) |

### How It Works
1. Initializes the SD card.
2. Deletes old files if they exist.
3. Writes numbers 0–5 to `"New.txt"`.
4. Reads the file and prints each line to the Serial Monitor.
5. Repeats every 5 seconds.

---

## Project 2: GPS Data Logger

### Description
This project reads **real-time GPS coordinates** from an Adafruit GPS module and logs them to an SD card (`GPSData.txt`). Each entry includes the **UTC time, latitude, and longitude**. This is ideal for geolocation logging, navigation tracking, or geofencing testing.

### Hardware Required
- Arduino (Uno, Mega, etc.)
- SD Card Module
- SD Card (FAT16/FAT32)
- Adafruit GPS Module
- Jumper wires

### Pin Configuration
| Component     | Arduino Pin |
|---------------|-------------|
| GPS RX/TX     | 3 (RX), 2 (TX) |
| SD Card CS    | 4           |
| SPI Pins      | 11 (MOSI), 12 (MISO), 13 (SCK) |
| Pin 10        | OUTPUT (required by SD library) |

### How It Works
1. Initializes GPS and SD card.
2. Deletes old log file if it exists.
3. Reads NMEA sentences from the GPS module.
4. Parses GPS data when a fix is available.
5. Writes UTC time, latitude, and longitude to `"GPSData.txt"` on the SD card.
6. Prints a message to the Serial Monitor each time data is logged.

---

## Notes
- Ensure the SD card is formatted as FAT16 or FAT32.
- Pin 10 must be set as OUTPUT for SD card initialization.
- GPS requires a clear view of the sky for accurate positioning.
- These projects can be extended to log sensor data alongside GPS coordinates.

---

## License
This repository is open-source and free to use for educational purposes.
