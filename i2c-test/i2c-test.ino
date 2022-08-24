
#include "Energia.h"
#include "Wire.h"
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop()
{
  Wire.requestFrom(0x68, 6);    // request 6 bytes from slave device #2

  while(Wire.available())    // slave may send less than requested
  { 
    byte c = Wire.read(); // receive a byte as character
    Serial.println(c, BIN);         // print the character
  }

  delay(500);
}
