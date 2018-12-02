#include "RAM23LC1024.h"

const uint8_t READ_CMD = 0x03; //Read starting at selected address
const uint8_t WRITE_CMD = 0x02; //Write data starting at selected address
//const uint8_t EDIO_CMD = 0x3B; //Enter dual I/O access
//const uint8_t EQIO_CMD = 0x38; //Enter Quad I/O mode
//const uint8_t RSTIO_CMD = 0xFF; //Reset to normal SPI mode
const uint8_t RDMR_CMD = 0x05; //Read mode register
const uint8_t WRMR_CMD = 0x01; //Write mode register

RAM23LC1024::RAM23LC1024(uint8_t _csPin, uint8_t _holdPin)
  : spiSettings(20000000, MSBFIRST, SPI_MODE0), csPin(_csPin), holdPin(_holdPin)
{  
}

void RAM23LC1024::begin(){
  pinMode(csPin, OUTPUT);
  pinMode(holdPin, OUTPUT);
  
  digitalWrite(csPin, HIGH);
  digitalWrite(holdPin, HIGH);
  
  SPI.begin();
  beginTransaction();
}

void RAM23LC1024::beginTransaction(){
  SPI.beginTransaction(spiSettings);
}

void RAM23LC1024::endTransaction(){
  SPI.endTransaction();
}

void RAM23LC1024::writeMode(uint8_t mode){
  digitalWrite(csPin, LOW); //Select device
  SPI.transfer(WRMR_CMD); //Send command
  SPI.transfer(mode & 0xC0); //Send data
  digitalWrite(csPin, HIGH); //Unselect device
}

uint8_t RAM23LC1024::readMode(){
  digitalWrite(csPin, LOW); //Select device
  SPI.transfer(RDMR_CMD); //Send command
  uint8_t data = SPI.transfer(0x00) & 0xC0; //Get data
  digitalWrite(csPin, HIGH); //Unselect device
  return data;
}

void RAM23LC1024::startWrite(uint32_t address){
  digitalWrite(csPin, LOW); //Select device
  SPI.transfer(WRITE_CMD); //Send command

  //Send 17-bit address
  SPI.transfer((uint8_t)((address >> 16) & 0x01));
  SPI.transfer((uint8_t)(address >> 8));
  SPI.transfer((uint8_t)address);
}

void RAM23LC1024::startRead(uint32_t address){
  digitalWrite(csPin, LOW); //Select device
  SPI.transfer(READ_CMD); //Send command

  //Send 17-bit address
  SPI.transfer((uint8_t)((address >> 16) & 0x01));
  SPI.transfer((uint8_t)(address >> 8));
  SPI.transfer((uint8_t)address);
}

void RAM23LC1024::stop(){
  digitalWrite(csPin, HIGH);
}

size_t RAM23LC1024::write(uint8_t c){
  SPI.transfer(c);
}

uint8_t RAM23LC1024::read(uint8_t c){
  return SPI.transfer(c);
}

void RAM23LC1024::startHold(){
  digitalWrite(holdPin, LOW);
}

void RAM23LC1024::stopHold(){
  digitalWrite(holdPin, HIGH);
}
