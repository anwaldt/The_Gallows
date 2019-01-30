#include "/home/anwaldt/Arduino/libraries/OSC/OSCMessage.h"

/*
Make an OSC message and send it over serial
 */

#ifdef BOARD_HAS_USB_SERIAL
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
#include <SLIPEncodedSerial.h>
 SLIPEncodedSerial SLIPSerial(Serial);
#endif


void setup() {
  //begin SLIPSerial just like Serial
  SLIPSerial.begin(9600);   // set this as high as you can reliably run on your platform
#if ARDUINO >= 100
  while(!Serial)
    ; //Leonardo "feature"
#endif
}


void loop(){
  
    float xVal = ((float) analogRead(A0) -512) /512;
    float yVal = ((float) analogRead(A1) -512) /512;
    float zVal = (float) (1000 -  analogRead(A2)) / 1000.0;
    
     
  OSCMessage msg1("/x");
  msg1.add(xVal);
  SLIPSerial.beginPacket();  
  msg1.send(SLIPSerial); // send the bytes to the SLIP stream
  SLIPSerial.endPacket(); // mark the end of the OSC Packet
  msg1.empty(); // free space occupied by message
  
  
  OSCMessage msg2("/y");
  msg2.add(yVal);
  SLIPSerial.beginPacket();  
  msg2.send(SLIPSerial); // send the bytes to the SLIP stream
  SLIPSerial.endPacket(); // mark the end of the OSC Packet
  msg2.empty(); // free space occupied by message


OSCMessage msg3("/z");
  msg3.add(zVal);
  SLIPSerial.beginPacket();  
  msg3.send(SLIPSerial); // send the bytes to the SLIP stream
  SLIPSerial.endPacket(); // mark the end of the OSC Packet
  msg3.empty(); // free space occupied by message




  delay(10);
}
