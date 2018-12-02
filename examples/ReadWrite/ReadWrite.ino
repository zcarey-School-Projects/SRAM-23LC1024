#include "RAM23LC1024.h"

/*
 * USE: 
 * Connect SCK to pin 13
 * Connect MISO to pin 12
 * Connect MOSI to pin 11
 */

const int csPin = 3;
const int holdPin = 2;

RAM23LC1024 RAM(csPin, holdPin);


const char testStr[] = "This... This is just a test!";

void setup() {
  RAM.begin();
  //RAM.beginTransaction() //Only used if SPI settings were set for a differnet device
  //RAM.endTransaction //Only call if you wish to use SPI settings for a different device

  Serial.begin(115200);
  Serial.println("Setting data mode...");
  RAM.writeMode(MODE_SEQUENTIAL);
  Serial.print("Checking... ");
  uint8_t mode = RAM.readMode();
  if(mode != MODE_SEQUENTIAL){
    Serial.println("Failed! Abort! Abort!!!");
    Serial.println(mode, HEX);
    Serial.println(mode & 0xC0, HEX);
    while(true){}
  }
  Serial.println("   Passed!");
  
  Serial.print("Okay, saving string '");
  Serial.print(testStr);
  Serial.println("'.");

  RAM.startWrite(0); //Takes in a 17-bit address
  RAM.print(testStr);
  RAM.write(0);
  RAM.stop(); //Deselects the device to stop the writing operation and free SPI to use on other devices.

  Serial.print("Read string: ");
  RAM.startRead(0); //Takes in 17-bit address
  printString();
  RAM.stop(); //Deselects the device to stop the reading operation and free SPI to use on other devices.

  Serial.print("\nRead Offset: ");
  RAM.startRead(8);
  printString();
  RAM.stop();

  Serial.print("\nHold demonstration: ");
  RAM.startRead(0);
  uint8_t i;
  for(i = 0; i < 8; i++){
    Serial.write(RAM.read());
  }
  RAM.startHold(); //Will ignore SPI data. This way other SPI devices can be used without stopping the current operation.
  for(i = 0; i < 12; i++){
    Serial.write(RAM.read()); //All chars will return 0 (since device is effectively disabled), so nothing will print to the monitor.
  }
  RAM.stopHold();
  for(i = 0; i < 20; i++){
    Serial.write(RAM.read());
  }
  RAM.stop();

  Serial.println("\nFinished!");
}

void loop() {
 
}

void printString(){
  while(true){
    uint8_t data = RAM.read();
    if(data == 0) break;
    Serial.write(data);
  }
  Serial.println();
}





