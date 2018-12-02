/*
 * RAM23LC1024.h - A library for using the 23LC1024 volatile memory chip.
 * Created by Zachary Carey
 * 12/1/2018 at 2:03pm
 * Released into the public domain.
 */

#ifndef _RAM23LC1024_h
#define _RAM23LC1024_h

#include "Arduino.h"
#include <SPI.h>

#define MODE_BYTE 0x00 //read/write one byte per command.
#define MODE_SEQUENTIAL 0x40 //Read/write goes through the entire memory array. at the end (0x1FFFF), wraps back to 0x00000
#define MODE_PAGE 0x80 //Read/write in pages. The device has 4096 pages of 32 bytes. When OP reaches end of page, it wraps around back to the beginning.

class RAM23LC1024 : public Print{
public:
  RAM23LC1024(uint8_t _csPin, uint8_t _holdPin);
  
  void begin();
  void beginTransaction();
  void endTransaction();

  void writeMode(uint8_t mode);
  uint8_t readMode();

  void startWrite(uint32_t address);
  void startRead(uint32_t address);

  void stop();

  size_t write(uint8_t);
  uint8_t read() { return read(0x00); }
  uint8_t read(uint8_t c);

  void startHold();
  void stopHold();

private:
  RAM23LC1024(){};

  SPISettings spiSettings;

  uint8_t csPin;
  uint8_t holdPin;

};

#endif //_RAM23LC1024_h