# SRAM 23LC1024 Arduino Library

Copyright (c) 2018 Zachary Carey (zcarey@ltu.edu), released under the MIT license.  
See the LICENSE file for licensing details.

This library wraps neccessary SPI protocol into easy-to-use methods

To start, begin() must be called. Doing this also sets the SPI settings to that of the SRAM device.

To change the data read/write mode, call writeMode(MODE), and select a mode from MODE_BYTE, MODE_SEQUENTIAL, or MODE_PAGE
MODE_BYTE: Will only read/write a single byte before returning null data.
MODE_SEQUENTIAL: Will read/write bytes until a stop() command is given. If the end of the memory array is reached, it will automatically wrap back to the beginning.
MODE_PAGE: Will read/write data in a single page. This particular device as 4096 pages of 32 bytes. Works like sequential, but ony affect data in one single page.

On the other hand, readMode() will read the mode register. This could be useful to check if the device is in the correct mode before operation.

To write data, first call startWrite(ADDRESS), where ADDRESS is a 17-bit number to start writing data at. After writing is finished, call stop() to stop the writing operation and free up SPI.

This library implements Arduino's Print class, so you may use all the normal function calls to write data (i.e. Serial.print);


To read data, first call startRead(ADDRESS), where ADDRESS is a 17-bit number to start reading data from. After reading is finished, call stop() to stop the reading operation and free up SPI.

To read data, you must call read(). This will return a single byte, assuming you already calles startRead().

startHold() will put the device into a "hold" state, will it will ignore all SPI transmissions. This is usefull if you need to use another SPI device without stopping your current read/write operation. Call stopHold() when finished to continue reading/writing.


## Class
The **RAM23LC1024** class takes two parameters on construction, the cs Pin and the hold Pin from the device.

## Functions

Function  | Description
------------- | -------------
**begin**  | Prepares SPI for use and calls beginTransaction().
**beginTransaction**  | Sets SPI settings to what is needed to communicate with the device. (MAX 20 MHz, MSB first, SPI Mode 0)
**endTransaction** | Frees SPI up to use on other devices.
**writeMode** | Sets the data mode operation for reading/writing.
**readMode** | Reads the currently set data mode operation from the device.
**startWrite** | Starts writing to volatile memory at the provided 17-bit address.
**startRead** | Starts reading from volatile memory at the provided 17-bit address.
**stop** | Stops reading or writing, and allows communication with other devices over SPI.
**write** | Writes a single byte to volatile memory, assuming startWrite has been called.
**read** | Returns a single byte read from volatile memory, assuming startRead has been called.
**startHold** | Puts the device into a hold state that causes it to ingore SPI communication.
**endHold** | Removes the device from it's hold state.

## Example

Here is a simple example of using the HX711 on pins A2 and A3 to read a strain gauge and print it's current value:

```c++
#include <Q2HX711.h>
Q2HX711 hx711(A2, A3);
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(hx711.read());
  delay(500);
}
```
