#include <Wire.h>
//SCL-22  SDA-21
#define ADDRESS_BH1750FVI 0x23  //ADDR="L" for this module

#define ONE_TIME_H_RESOLUTION_MODE 0x20

//One Time H-Resolution Mode:

//Resolution = 1 lux

//Measurement time (max.) = 180ms

//Power down after each measurement

byte highByte = 0;

byte lowByte = 0;

unsigned int sensorOut = 0;

unsigned int illuminance = 0;



void setup(){

   Wire.begin();

   Serial.begin(115200);

}



void loop(){

   Wire.beginTransmission(ADDRESS_BH1750FVI); //"notify" the matching device

   Wire.write(ONE_TIME_H_RESOLUTION_MODE);   //set operation mode

   Wire.endTransmission();

   delay(180);

   Wire.requestFrom(ADDRESS_BH1750FVI, 2); //ask Arduino to read back 2 bytes from the sensor

   highByte = Wire.read(); // get the high byte

   lowByte = Wire.read(); // get the low byte

   sensorOut = (highByte<<8)|lowByte;

   illuminance = sensorOut/1.2;

   Serial.print(illuminance);  Serial.println(" lux");

   delay(5000);

}



