// Demo board
#include "Energia.h"
#include "i2c.h"
#include "imu.h"

MPU6050 imu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {  
  Serial.begin(9600); // Serial monitor
  Serial.println("Starting...");
  Wire.begin(); // Start I2C
  imu.initialize();  
  Serial.println("Testing device connection...");
  if (imu.testConnection()){
    Serial.println("MPU6050 connection successful");
  }else{
    Serial.println("MPU6050 connection failed");
    exit(0);
  }
}

void loop() {
  imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // read measurements from device

  // display tab-separated accel/gyro x/y/z values
  Serial.print("a/g:\t");
  Serial.print(ax);
  Serial.print("\t");
  Serial.print(ay);
  Serial.print("\t");
  Serial.print(az);
  Serial.print("\t");
  Serial.print(gx);
  Serial.print("\t");
  Serial.print(gy);
  Serial.print("\t");
  Serial.println(gz);
}
