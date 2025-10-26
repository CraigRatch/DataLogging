/*
  Project: Arduino SD Card Test
  Author: Craig Ratchford
  Description:
    This Arduino program demonstrates a simple SD card test. 
    It writes numbers (0–5) to a text file on the SD card and reads them back,
    printing the results to the Serial Monitor. This is useful for learning 
    file handling, debugging, and data logging on Arduino.
*/

#include <SD.h>  // Include SD card library
#include <SPI.h> // Include SPI library for SD communication

const int chipSelect = 9; // Pin connected to CS/SS of SD card module

void setup() {
  Serial.begin(9600);       // Start Serial Monitor at 9600 baud
  pinMode(10, OUTPUT);      // Required by SD library for some modules

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    while (1); // Halt program if SD card is not detected
  }
  Serial.println("SD card initialized.");

  // Remove old files if they exist
  if (SD.exists("test.txt")) SD.remove("test.txt");
  if (SD.exists("New.txt"))  SD.remove("New.txt");
}

void loop() {
  // Open "New.txt" for writing (creates it if it doesn't exist)
  File file = SD.open("New.txt", FILE_WRITE);

  // Write numbers 0–5 into the file
  for (int i = 0; i < 6; i++) {
    file.println(i);
  }
  file.close(); // Close file to save changes
  Serial.println("Data written to file successfully!");

  delay(5000); // Wait 5 seconds

  // Open "New.txt" for reading
  file = SD.open("New.txt", FILE_READ);

  // Read and print each line to Serial Monitor
  for (int i = 0; i < 6; i++) {
    String line = file.readStringUntil('\n');
    Serial.println(line);
  }
  file.close(); // Close file
}
