#include <Wire.h>
#include "Adafruit_SGP30.h"
#include "DHT.h"

Adafruit_SGP30 sgp;





#define ADDRESS_BH1750FVI 0x23    //ADDR="L" for this module
#define ONE_TIME_H_RESOLUTION_MODE 0x20

byte highByte = 0;
byte lowByte = 0;
unsigned int sensorOut = 0;
unsigned int illuminance = 0;




void setup() {
  
  Wire.begin();
  Serial.begin(115200);
  while (!Serial) {delay(10);} // Wait for serial console to open!

  sgp.begin();
}


void loop() {
  Wire.beginTransmission(ADDRESS_BH1750FVI); //"notify" the matching device
  Wire.write(ONE_TIME_H_RESOLUTION_MODE);     //set operation mode
  Wire.endTransmission();
         
  delay(180);

  Wire.requestFrom(ADDRESS_BH1750FVI, 2); //ask Arduino to read back 2 bytes from the sensor
  highByte = Wire.read();  // get the high byte
  lowByte = Wire.read(); // get the low byte
     
  sensorOut = (highByte<<8)|lowByte;
  illuminance = sensorOut/1.2;
  

//  Serial.println("*C");

  sgp.IAQmeasure();
  //SGP30数据输出
  Serial.print("TVOC "); 
  Serial.print(sgp.TVOC);

  Serial.println(" ppb\t");

  Serial.print("eCO2 "); 
  Serial.print(sgp.eCO2);
  Serial.println(" ppm");

  sgp.IAQmeasureRaw();
  Serial.print("Raw H2 "); 
  Serial.println(sgp.rawH2); 

//  Serial.print(" \t");

  Serial.print("Raw Ethanol "); 
  Serial.println(sgp.rawEthanol);  
//  Serial.println("");  


  delay(1000);
}
