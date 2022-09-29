#include "Energia.h"
#include "Xbee.h"

// Debug Mode -- Uncomment line below to enable
#define DEBUG_MODE

// Demo BOard
// 0013A20041BA172C

// For receiving data from Xbee
int xbee_byte;
int xbee_str[100];
byte xbee_index = 0;
bool dataXbee = false;

// For receiving data from server (Serial port)
char server_byte;
String server_str = "";
bool dataServer = false;

// For timeouts in communication loops
unsigned int timer = 0;

#define SENSOR_ADDRESS "0013A20041BA172C"
#define timeout 5000uL      // Timeout for receiving next serial byte of data
#define MSG_TIMEOUT 10000uL // Time in milliseconds to timeout Transmit frames

// Available commands
#define GYRO "GYRO"
#define POT "POT"
#define SWITCH "SWITCH"
#define ALL "ALL"

void SendFrame(String frame);
bool CheckValidFrame();
String GetTransmitMessage();
int GetFrameLength();
String GetSenderAddress();
bool SendMessage(String message, String address);
bool WaitForResponse(unsigned long loop_timeout);
bool ReceiveMessage();

void setup()
{
  // Start serial communication
  Serial.begin(9600);
  while (!Serial)
  {
    // Wait for serial port to connect
  }
  Serial1.begin(9600);
  while (!Serial1)
  {
    ; // Wait for serial port to connect
  }
  // Print Instructions
  Serial.println(F("Starting Demo Board.."));
  Serial.println(F("\nAvailable Commands:"));
  Serial.println(F("1. GYRO - Gyroscope data"));
  Serial.println(F("2. POT - Potentiometer voltage"));
  Serial.println(F("3. SWITCH - On/Off status"));
  Serial.println(F("4. ALL - To request all sensor data"));
}

void loop()
{
  // Clear index every main loop
  xbee_index = 0;

  // If there is incoming data from COM port
  if (Serial.available())
  {
    timer = 0; // CLear timer
    while (timer < timeout)
    {          // While haven't reached serial data timeout
      timer++; // Increment timer
      while (Serial.available())
      {
        timer = 0;                   // Reset timer every time a byte arrives to buffer
        server_byte = Serial.read(); // Read the next byte
        if (server_byte != '\0')
        {                            // If the byte isn't NULL
          server_str += server_byte; // Append to the string to be sent
        }
      }
    }
    dataServer = true; // Set flag as true
  }

  if (dataServer)
  {
    dataServer = false; // Clear flag
    if (server_str != "")
    {
#ifdef DEBUG_MODE
      Serial.print(F("\nData from COM port: "));
      Serial.println(server_str);
#endif
      if (server_str == GYRO)
      {
        Serial.println(F("\nRequesting Gyroscope Data.."));
        bool tx_status = SendMessage(GYRO, SENSOR_ADDRESS);
        if (tx_status == true)
        {
          // Check the response
          bool msg_rx = ReceiveMessage();
          if (msg_rx == true)
          {
            // Parse through the data
            String data_message = GetTransmitMessage();
            Serial.print(F("\nGyroscope Data: "));
            Serial.println(data_message);
            xbee_index = 0;
          }
          else
          {
            Serial.println(F("Sensor Board Timed Out"));
          }
        }
        else
        {
          Serial.println(F("Unable to reach sensor board"));
        }
      }
      else if (server_str == POT)
      {
        Serial.println(F("\nRequesting Potentiometer Data.."));
        bool tx_status = SendMessage(POT, SENSOR_ADDRESS);
        if (tx_status == true)
        {
          // Check the response
          bool msg_rx = ReceiveMessage();
          if (msg_rx == true)
          {
            // Parse through the data
            String data_message = GetTransmitMessage();
            Serial.print(F("\nPotentiometer Data: "));
            Serial.println(data_message);
            xbee_index = 0;
          }
          else
          {
            Serial.println(F("Sensor Board Timed Out"));
          }
        }
        else
        {
          Serial.println(F("Unable to reach sensor board"));
        }
      }
      else if (server_str == SWITCH)
      {
        Serial.println(F("\nRequesting Switch Status.."));
        bool tx_status = SendMessage(SWITCH, SENSOR_ADDRESS);
        if (tx_status == true)
        {
          // Check the response
          bool msg_rx = ReceiveMessage();
          if (msg_rx == true)
          {
            // Parse through the data
            String data_message = GetTransmitMessage();
            Serial.print(F("\nSwitch Status: "));
            Serial.println(data_message);
            xbee_index = 0;
          }
          else
          {
            Serial.println(F("Sensor Board Timed Out"));
          }
        }
        else
        {
          Serial.println(F("Unable to reach sensor board"));
        }
      }
      else if (server_str == ALL)
      {
        Serial.println(F("\nRequesting All Sensor Data.."));
        bool tx_status = SendMessage(ALL, SENSOR_ADDRESS);
        if (tx_status == true)
        {
          // Check the response
          bool msg_rx = ReceiveMessage();
          if (msg_rx == true)
          {
            // Parse through the data
            String data_message = GetTransmitMessage();
            Serial.print(F("\nAll Sensor Data: "));
            Serial.println(data_message);
            xbee_index = 0;
          }
          else
          {
            Serial.println(F("Sensor Board Timed Out"));
          }
        }
        else
        {
          Serial.println(F("Unable to reach sensor board"));
        }
      }
      else
      {
        Serial.println(F("Invalid selection"));
      }
    }
    server_str = ""; // Clear string for future use
  }
}

// Send specified frame through XBee port
void SendFrame(String frame)
{
  if (frame != "")
  {
    int data_length = frame.length();
    // DEGUB Serial.print(F("Sending: "));
    for (int i = 0; i < data_length; i += 2)
    {
      int first = CharToHex(frame.charAt(i));
      int second = CharToHex(frame.charAt(i + 1));
      int byte_value = (first * 16) + second;
      Serial1.write(byte_value);
#ifdef DEBUG_MODE
      if (byte_value < 0x10)
      {
        Serial.print(F("0"));
      }
      Serial.print(byte_value, HEX);
      Serial.print(F(" "));
#endif
    }
  }
  Serial.println();
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
#ifdef DEBUG_MODE
      Serial.println(F("Invalid Frame"));
#endif
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

// Parse through Transmit data frame for the sender's address
String GetSenderAddress()
{
  // Get the 64-bit source address (coordinator MAC)
  String sender_addr = "";
  for (int i = 4; i < 12; i++)
  {
    String value = "00";
    if (xbee_str[i] < 0x10)
    {
      String temp = String(xbee_str[i], HEX);
      value[1] = temp[0];
    }
    else
    {
      value = String(xbee_str[i], HEX);
    }
    sender_addr += value;
  }
  sender_addr.toUpperCase();
  return sender_addr;
}

// Send a Transmission with the specified message to the specified address. Will wait for a response status for a duration specified by <MSG_TIMEOUT>
bool SendMessage(String message, String address)
{
  int frameID = random(0x01, 0xFF); // ID for matching status
  String frameID_str = CreateFrameID(frameID);
  String frame = Transmit(frameID_str, address, "FFFE", "00", "00", message);
  Serial.print(F("\nSending message: "));
  Serial.println(message);
  SendFrame(frame);
  // Wait for a response message
  bool receivedSuccess = false;           // Flag for Transmit Status response
  unsigned long responseStart = millis(); // Get the vurrent time for the reponse
  unsigned long responseTime = 0;
  do
  {
    responseTime = millis() - responseStart; // Get the total response time at the beggining of each loop
    bool msg_rx = WaitForResponse(5000);     // Wait for a response frame
    if (msg_rx == true)
    { // If a message has arrived
      if (CheckValidFrame())
      {
        // Check if it's a transmit status AND frameID matches with Transmission
        receive_type rx_type = ReceiveAPI(xbee_str[3]);
        if ((rx_type == EXT_TX_STATUS) && (xbee_str[4] == frameID))
        {
          // Check if Transmit frame was successful
          if (xbee_str[8] == 0x00)
          {
            receivedSuccess = true;
            xbee_index = 0; // Clear index for future use
            break;
          }
          else
          {
            Serial.print(F("Message Transmission failed with code: "));
            Serial.println(xbee_str[8], HEX);
            xbee_index = 0; // Clear index for future message
          }
        }
        else
        {                 // Received a valid frame, but not Transmit status with matching frameID
          xbee_index = 0; // Clear index for next message to be received
        }
      }
    }
  } while (responseTime < MSG_TIMEOUT); // While response not successful or timer less than timeout
  // Return true if transmission was success
  if (receivedSuccess == true)
  {
    Serial.println(F("Message Transmission Successful"));
    return true;
  }
  else
  {
    // If message transmission time out
    Serial.println(F("Error -- SendMessage timeout"));
    return false;
  }
}

// Wait for a response from Xbee port. Exit loop after <loop_timeout> loops
bool WaitForResponse(unsigned long loop_timeout)
{
  xbee_index = 0;              // Clear index to be ready for response
  long response_timer = 0;     // Loop timer for receiving the serial data
  unsigned long loop_time = 0; // Start time, used for timeout
  do
  {
    loop_time++; // Update loop time
    if (Serial1.available())
    { // When data arrives
      while (response_timer < timeout)
      {                   // Bytes might take some time to arrive after another
        response_timer++; // Incrememnt loop timer
        while (Serial1.available())
        {                                   // When next data byte arrives
          response_timer = 0;               // Clear loop timer
          xbee_byte = Serial1.read();       // Read the next byte
          xbee_str[xbee_index] = xbee_byte; // Add byte to array
          xbee_index++;                     // Increment index
        }
      }
    }
  } while ((xbee_index == 0) && (loop_time < loop_timeout)); // Wait for response until data arrives or timeout limit is reached
  if (xbee_index != 0)
  { // If there is a reponse
#ifdef DEBUG_MODE
    Serial.print(F("Received in WaitForResponse: "));

    for (int i = 0; i < xbee_index; i++)
    {
      if (xbee_str[i] < 0x10)
      {

        Serial.print("0");
      }
      Serial.print(xbee_str[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
#endif
    return true;
  }
  else
  { // If there was no received response (timed-out)
    return false;
  }
}

// Returns true if the received message is from Command Center and the data frame contains the message specified by the message parameter
bool ReceiveMessage()
{
#ifdef DEBUG_MODE
  Serial.println(F("Waiting for message"));
#endif
  unsigned long responseStart = millis(); // Get the current time
  unsigned long responseTime = 0;         // To get the response time each loop
  bool msg_rx = false;                    // Flag for receiving any message
  bool msg_success = false;               // Flag for receiving the specified message
  xbee_index = 0;
  do
  {                                          // Timeout loop
    responseTime = millis() - responseStart; // Current time for the loop
    msg_rx = WaitForResponse(10000);
    if (msg_rx == true)
    { // If a message has arrived
      if (CheckValidFrame())
      { // If the message is a valid data frame
        if (xbee_str[3] == 0x91)
        { // If received message is a Transmit message
#ifdef DEBUG_MODE
          String rx_data = GetTransmitMessage();
          Serial.print(F("Message received: "));
          Serial.println(rx_data);
#endif
          msg_success = true;
          break;
        }
        else
        { // If received different kind of frame
          Serial.println(F("Error - Not recieved a Transmit message"));
          xbee_index = 0; // Clear for future use
        }
      }
    }
  } while (responseTime < MSG_TIMEOUT);
  // After timeout loop
  if (msg_success == true)
  {
    return true;
  }
  else
  {
    Serial.println(F("Error - ReceiveMessage Timeout"));
    return false;
  }
}
