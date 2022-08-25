// Demo board
#include "Energia.h"
#include <Wire.h>
#include <MPU6050.h>
#include "Xbee.h"

// Debug Mode -- Uncomment line below to enable
#define DEBUG_MODE

// Demo Board
// 0013A20041BA172C

MPU6050 mpu;

// Timers
unsigned long sensor_timer = 0;
unsigned long lastReadingTime = 0;
float timeStep = 0.01; // Value in seconds

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

int analogValue = 0;
bool light = false;

// For timeouts in communication loops
unsigned int timer = 0;
// Timeout for receiving next serial byte of data
#define timeout 5000uL

// For receiving data from Xbee
int xbee_byte;
int xbee_str[100];
byte xbee_index = 0;
bool dataXbee = false;

// For receiving data from server (Serial port)
char server_byte;
String server_str = "";
bool dataServer = false;

// Debug
int count = 0;

// Available commands
#define GYRO "GYRO"
#define POT "POT"
#define SWITCH "SWITCH"
#define ALL "ALL"

bool CheckValidFrame();
String GetTransmitMessage();
int GetFrameLength();

void setup()
{
  // Initialize Serial Com
  Serial.begin(115200);
  while (!Serial)
  {
    // Wait for serial port to connect
  }
  Serial.println("Starting Demo Sensor Board");

  // Initialize Xbee Serial Com
  Serial1.begin(9600);
  while (!Serial1)
  {
    ; // Wait for serial port to connect
  }

  // Initialize MPU6050
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  // Calibrate gyroscope, calibration must be at rest
  mpu.calibrateGyro();
  // Set threshold sensivty. Default 3.
  mpu.setThreshold(3);
}

void loop()
{
  xbee_index = 0;

  if (Serial1.available())
  {
    timer = 0; // Clear timer
    while (timer < timeout)
    {          // While haven't reached serial data timeout
      timer++; // Incrememnt timer
      while (Serial1.available())
      {                                   // While there is data to receive
        timer = 0;                        // Reset timer every time a byte arrives to buffer
        xbee_byte = Serial1.read();       // Read the next byte
        xbee_str[xbee_index] = xbee_byte; // Append the string of received data
        xbee_index++;                     // Incremement the index of the C-style string to point to next unused location
      }
    }
    dataXbee = true; // Set flag as true
  }

  if ((dataXbee == true) && (xbee_index != 0))
  {
    dataServer = false;
#ifdef DEBUG_MODE
    Serial.print(F("\nReceived message: "));
    for (int i = 0; i < xbee_index; i++)
    {
      if (xbee_str[i] < 0x10)
      {
        Serial.print(F("0")); // Append with a 0 if value is less than 0x10
      }
      Serial.print(xbee_str[i], HEX);
      Serial.print(F(" ")); // Print byte value
    }
    Serial.println();
#endif
    // Decode the incoming data
    if (CheckValidFrame())
    {
      receive_type rx_type = ReceiveAPI(xbee_str[3]); // Get the receive API type
      if (rx_type == EXPL_RX_IND)
      {
        String rx_data = GetTransmitMessage(); // Store Transmit message
#ifdef DEBUG_MODE
        Serial.print(F("Data received: "));
        Serial.println(rx_data);
#endif
      }
      else
      {
#ifdef DEBUG_MODE
        Serial.print(F("Frame is of API type: "));
        Serial.print(rx_type);
        Serial.println(F(" -- Type not supported"));
#endif
      }
    }
  }
  else
  {
    count++;
    sensor_timer = millis();

    // Read normalized values
    Vector norm = mpu.readNormalizeGyro();

    // Calculate Pitch, Roll and Yaw
    pitch = pitch + norm.YAxis * timeStep;
    roll = roll + norm.XAxis * timeStep;
    yaw = yaw + norm.ZAxis * timeStep;

    // Analog Voltage
    analogValue = analogRead(28);
    float analog = ((float)(analogValue) / 1023) * 3.3;

    // Digital LED status
    light = digitalRead(11);

    if (count > 15)
    {
#ifdef DEBUG_MODE
      // Output raw
      Serial.print("\n Pitch = ");
      Serial.print(pitch);
      Serial.print(" Roll = ");
      Serial.print(roll);
      Serial.print(" Yaw = ");
      Serial.print(yaw);
      Serial.print(" Analog Voltage: ");
      Serial.print(analog);
      Serial.print(" LED : ");
      light ? Serial.println("ON\n") : Serial.println("OFF\n");
      count = 0;
#endif
    }

    // Wait to full timeStep period
    delay((timeStep * 1000) - (millis() - sensor_timer));
  }
}

// Returns true if start delimiter is valid and if the calculated checksum matches checksum byte, false otherwise
bool CheckValidFrame()
{
  if (xbee_index == 0)
  { // Check if xbee_str was unchanged
    return false;
  }
  else
  {
    int frame_length = (xbee_str[1] * 0x100) + xbee_str[2]; // Get the value of frame length
    byte checksum = 0;                                      // To create calculated checksum
    for (int i = 0; i < frame_length; i++)
    {
      checksum += xbee_str[3 + i]; // Add all the bytes from the 'data' in the frame
    }
    checksum = 0xFF - checksum; // As per datasheet
    // Check valid start delimeter and matching checksum values
    if ((xbee_str[0] == 0x7E) && (checksum == xbee_str[3 + frame_length]))
    {
      return true;
    }
    else
    {
      xbee_index = 0; // Clear the index since message is not valid
      Serial.println(F("Invalid Frame"));
      return false;
    }
  }
}

// Parse through Transmit data frame for the data (message)
String GetTransmitMessage()
{
  // Get the data from Transmit message (Truck ID)
  int frame_length = GetFrameLength();
  String rx_data = "";
  for (int i = 21; i < frame_length + 3; i++)
  {
    char c = xbee_str[i];
    rx_data += c;
  }
  return rx_data;
}

// Returns value specified by the two bytes in rx_str corresponding to the length of the data frame
int GetFrameLength()
{
  return ((xbee_str[1] * 0x100) + xbee_str[2]);
}
