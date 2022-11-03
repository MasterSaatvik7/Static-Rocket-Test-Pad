#include <Arduino.h>
#include "HX711.h"
#include <SPI.h>
#include <SD.h>
#include "Adafruit_MAX31855.h"

/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */
#define MAXDO   12
#define MAXCS1  A2
#define MAXCS2  A1
#define MAXCLK  13
// initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS1, MAXDO);
Adafruit_MAX31855 thermocouple2(MAXCLK, MAXCS2, MAXDO);
File myFile;
File myFileTemp;
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;
const int IGNITION = 15;
const int SWITCH = 7;
double c;
double c_2;
HX711 scale;


void setup() {
// Open serial communications and wait for port to open:
  Serial.begin(57600);
 
//LOAD CELL 
  Serial.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)
            
  scale.set_scale(36.059);
  //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");

  //THERMOCOUPLE

  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc

  Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
  Serial.print("Initializing sensor...");
  if (!thermocouple.begin()) {
    Serial.println("ERROR.");
    while (1) delay(10);
  }

  // OPTIONAL: Can configure fault checks as desired (default is ALL)
  // Multiple checks can be logically OR'd together.
  // thermocouple.setFaultChecks(MAX31855_FAULT_OPEN | MAX31855_FAULT_SHORT_VCC);  // short to GND fault is ignored

  Serial.println("DONE.");

  //SD CARD
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("TEST_DATA.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    
    Serial.print("Writing to TEST_DATA.txt...");
    myFile.print(scale.get_units()/1000, 1);  //OUTPUT
    myFile.print("\t \t");
    myFile.print(scale.get_units(10), 5);
    myFile.print("\t \t");
//    myFile.print("C1= ",c);
//    myFile.print("C2= ",c_2);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening TEST_DATA.txt");
  }

  
  }

/*  // re-open the file for reading:
  myFile = SD.open("TEST_DATA.txt");
  if (myFile) {
    Serial.println("TEST_DATA.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening TEST_DATA.txt");
  }
  */



void loop() {
  if (digitalRead(SWITCH) == HIGH){
    delay(10000);
    digitalWrite(IGNITION,HIGH);
  }
  Serial.print("Weight in KG:\t");
  Serial.print(scale.get_units()/1000, 1);
  Serial.print("\t| average:\t");
  Serial.print(scale.get_units(10), 5);

  delay(10);
  Serial.print("\t \t");
   // basic readout test, just print the current temp
   Serial.print("Internal Temp = ");
   Serial.println(thermocouple.readInternal());

   double c = thermocouple.readCelsius();
   double c_2 = thermocouple2.readCelsius();
   if (isnan(c || c_2)) {
     Serial.println("Thermocouple fault(s) detected!");
     uint8_t e = thermocouple.readError();
     uint8_t e2 = thermocouple2.readError();
     if (e & MAX31855_FAULT_OPEN || e2 & MAX31855_FAULT_OPEN) Serial.println("FAULT: Thermocouple is open - no connections.");
     if (e & MAX31855_FAULT_SHORT_GND || e2 & MAX31855_FAULT_SHORT_GND) Serial.println("FAULT: Thermocouple is short-circuited to GND.");
     if (e & MAX31855_FAULT_SHORT_VCC || e2 & MAX31855_FAULT_SHORT_VCC) Serial.println("FAULT: Thermocouple is short-circuited to VCC.");
   } else {
     Serial.print("C1 = ");
     Serial.print(c);
     Serial.print("\t C2 = ");
     Serial.println(c_2);
   }

   myFileTemp = SD.open("TEST_Temp_DATA.txt", FILE_WRITE);
  if (myFileTemp){
 //   myFileTemp.print("C1 = ", c);
    myFileTemp.print("\t \t");
//    myFileTemp.println("C2 = ", c_2);
    myFileTemp.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening TEST_DATA.txt");
  }
   //Serial.print("F = ");
   //Serial.println(thermocouple.readFahrenheit());

   delay(100);
}
