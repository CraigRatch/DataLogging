/*
  Project: Arduino GPS Data Logger to SD Card
  Author: Craig Ratchford
  Description:
    This program reads GPS coordinates from an Adafruit GPS module
    and logs them to an SD card. Each entry includes latitude, longitude,
    and the UTC time from the GPS. This can be used for geolocation tracking,
    navigation logging, or testing geofencing systems.
*/

#include <SD.h>          // SD card library
#include <SPI.h>         // SPI library (required by SD)
#include <Adafruit_GPS.h> // GPS library
#include <SoftwareSerial.h> // Software serial for GPS

// Pins
SoftwareSerial mySerial(3, 2); // RX, TX for GPS
Adafruit_GPS GPS(&mySerial);
const int chipSelect = 4;       // CS pin for SD card

// File object
File gpsLogFile;

void setup() {
  Serial.begin(115200);   // Serial monitor for debugging
  GPS.begin(9600);        // Start GPS at 9600 baud
  GPS.sendCommand(PGCMD_ANTENNA);              // Reduce antenna noise
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // Request RMC + GGA sentences
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // Update rate: 1Hz
  delay(1000);

  // SD card initialization
  pinMode(10, OUTPUT); // Required by SD library
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    while (1); // Halt if SD fails
  }
  Serial.println("SD card initialized.");

  // Remove old log file if exists
  if (SD.exists("GPSData.txt")) {
    SD.remove("GPSData.txt");
  }
}

void loop() {
  // Read GPS data
  char c = GPS.read();
  if (GPS.newNMEAreceived()) {
    GPS.parse(GPS.lastNMEA()); // Parse the new NMEA sentence
  }

  // Only log when we have a fix
  if (GPS.fix) {
    // Open file for appending
    gpsLogFile = SD.open("GPSData.txt", FILE_WRITE);
    if (gpsLogFile) {
      // Write timestamp and coordinates
      gpsLogFile.print("Time: ");
      gpsLogFile.print(GPS.hour); gpsLogFile.print(":");
      gpsLogFile.print(GPS.minute); gpsLogFile.print(":");
      gpsLogFile.print(GPS.seconds); gpsLogFile.print(" UTC, ");
      gpsLogFile.print("Lat: "); gpsLogFile.print(GPS.latitude, 6);
      gpsLogFile.print(", Lon: "); gpsLogFile.println(GPS.longitude, 6);

      gpsLogFile.close(); // Close file
      Serial.println("GPS data logged to SD card.");
    } else {
      Serial.println("Error opening file for writing.");
    }
    delay(1000); // Wait before logging next fix
  }
}
