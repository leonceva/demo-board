// .cpp for XBEE API mode frames
#include "Energia.h"
#include "Xbee.h"
#include "Frames.h"

/* *************************************************************************************
   Transmit General Functions
 * ************************************************************************************/
// Function to convert a String into an ASCII value representation of type String
// such that each character is converted into a hexadecimal byte value for
// the respective character
String Ascii_to_Hex(String input)
{
  int input_length = input.length();  // get length of input string
  char input_array[input_length + 1]; // make a buffer to hold the characters

  for (int i = 0; i < input_length + 1; i++)
  {
    input_array[i] = input.charAt(i); // transfer the characters
  }

  char output_array[(input_length * 2) + 1]; // buffer for hex values to be twice as long +1
  int loop = 0;
  int i = 0;

  while (input_array[loop] != '\0')
  {                                                                 // checking null termination
    sprintf((char *)(output_array + i), "%02X", input_array[loop]); // conversion to hex value
    loop += 1;                                                      // next char
    i += 2;                                                         // each value takes 2 places in output_array
  }
  output_array[i++] = '\0'; // insert NULL at the end of the output string
  String output = String(output_array);
  return output;
}

// Function to take a char and convert it to its Hex value
short CharToHex(char character)
{
  short value;
  switch (character)
  {
  case '0':
    value = 0;
    break;
  case '1':
    value = 1;
    break;
  case '2':
    value = 2;
    break;
  case '3':
    value = 3;
    break;
  case '4':
    value = 4;
    break;
  case '5':
    value = 5;
    break;
  case '6':
    value = 6;
    break;
  case '7':
    value = 7;
    break;
  case '8':
    value = 8;
    break;
  case '9':
    value = 9;
    break;
  case 'A':
    value = 10;
    break;
  case 'B':
    value = 11;
    break;
  case 'C':
    value = 12;
    break;
  case 'D':
    value = 13;
    break;
  case 'E':
    value = 14;
    break;
  case 'F':
    value = 15;
    break;
  case NULL:
    value = 0;
    break;
  }
  return value;
}

// Function to create 'checksum' field for the transmission frame
String CheckSum(String data)
{
  int data_length = data.length(); // length of data string
  char data_char[data_length];     // buffer to hold the characters in data
  for (int i = 0; i < data_length + 1; i++)
  {
    data_char[i] = data.charAt(i); // transfer characters
  }
  byte sum = 0;
  for (int i = 0; i < (data_length / 2); i++)
  { // get two characters at a time to sum bytes
    char first_c = data_char[2 * i];
    int first_int = CharToHex(first_c);
    char second_c = data_char[(2 * i) + 1];
    int second_int = CharToHex(second_c);
    sum = sum + (first_int * 16) + second_int; // first character in byte to be multiplied with power of 16^1
  }
  sum = 0xFFFF - sum; // as per datasheet
  if (sum < 0x10)
  {
    String checksum = '0' + String(sum, HEX);
    checksum.toUpperCase();
    return checksum;
  }
  else
  {
    String checksum = String(sum, HEX);
    checksum.toUpperCase();
    return checksum;
  }
}

// Function to create 'length' field for the transmission frame
String CreateLength(String data)
{
  int length_int = data.length(); // length of 'data' in the data frame
  length_int = length_int / 2;
  String length_str = String(length_int, HEX);

  // pad with preceding '0' if needed
  if (length_int < 0x10)
  {
    length_str = String("000" + length_str);
  }
  else
  {
    if (length_int < 0x100)
    {
      length_str = String("00" + length_str);
    }
    else
    {
      if (length_int < 0x1000)
      {
        length_str = String('0' + length_str);
      }
    }
  }

  length_str.toUpperCase();
  return length_str;
}

// Function to create the entire frame to be sent
String CreateFrame(String data)
{
  String length_frame = CreateLength(data);
  String checksum = CheckSum(data);
  String frame = START + length_frame + data + checksum;
  return frame;
}

// Function to create a string for Frame ID
String CreateFrameID(int value)
{
  char buffer[2]; // to hold value as a string
  sprintf((char *)(buffer), "%02X", value);
  String frame_ID = String(buffer);
  return frame_ID;
}

// Function to convert the string containing hex-valued characters to its value
int String_to_Value(String string)
{
  int string_value = 0;
  int string_length = string.length();
  for (int i = 0; i < (string_length); i++)
  {
    char c = string.charAt(i);
    int value = CharToHex(c);
    for (int j = (string_length - 1 - i); j > 0; j--)
    {
      value *= 16;
    }
    string_value += value; // sum the values of all characters
  }
  return string_value;
}

// Function to store the received data
String ReadIncomingData()
{
  String message = "";           // to store the incoming data
  message = Serial.readString(); // read the data as a string for ease of splitting it up in further functions
  return message;
}

// Function to check the start delimeter
bool CheckStart(String first_byte)
{
  if (first_byte == START)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Function to convert  an ASCII value representation of type String into a String
// such that each 2-char value is converted into the respective character
String Hex_to_Ascii(String input)
{
  int input_length = input.length();
  char input_array[input_length + 1]; // make a buffer to hold the characters

  for (int i = 0; i < input_length + 1; i++)
  {
    input_array[i] = input.charAt(i); // transfer the characters
  }

  char output_array[(input_length / 2) + 1]; // buffer for characters to be half as long +1
  int msb_value = 0;
  int lsb_value = 0;
  int value = 0;
  int loop = 0;
  int i = 0;
  while (input_array[loop] != '\0')
  {                                                   // checking null termination
    msb_value = (input_array[loop] - 48) * 16;        // first byte value *16
    lsb_value = input_array[loop + 1] - 48;           // second byte value
    value = msb_value + lsb_value;                    // sum to get character value
    sprintf((char *)(output_array + i), "%c", value); // conversion to character
    loop += 2;
    i += 1;
  }
  output_array[i++] = '\0'; // insert NULL at the end of the output string
  String output = String(output_array);
  return output;
}

// Function to return the string needed for AT Command field of data frame
String DefineATCommand(AT_type at_type)
{
  String output = "";
  switch (at_type)
  {
  case AVAIL_FREQ:
    output = "4146";
    break;
  case CHANNEL_MASK:
    output = "434D";
    break;
  case MIN_FREQ:
    output = "4D46";
    break;
  case PREAMBLE_ID:
    output = "4850";
    break;
  case NETWORK_ID:
    output = "4944";
    break;
  case BROAD_MULTI_TX:
    output = "4D54";
    break;
  case TX_POWER_LEVEL:
    output = "504C";
    break;
  case UNICAST_RETRIES:
    output = "5252";
    break;
  case BYTES_TX:
    output = "4243";
    break;
  case LAST_PKT_RSSI:
    output = "4442";
    break;
  case RX_ERROR_COUNT:
    output = "4552";
    break;
  case GOOD_PKT_RX:
    output = "4744";
    break;
  case MAC_ACK_FAIL_COUNT:
    output = "4541";
    break;
  case TX_FAIL_COUNT:
    output = "5452";
    break;
  case UNICAST_ATT_COUNT:
    output = "5541";
    break;
  case MAC_UNI_HOP_TIME:
    output = "2548";
    break;
  case MAC_BORAD_HOP_TIME:
    output = "2538";
    break;
  case ROUTING_MSG_MODE:
    output = "4345";
    break;
  case BROADCAST_HOPS:
    output = "4248";
    break;
  case NETWORK_HOPS:
    output = "4E48";
    break;
  case MESH_UNI_RETRIES:
    output = "4D52";
    break;
  case NETWORK_DELAY_SLOTS:
    output = "4E4E";
    break;
  case SERIAL_NUM_HIGH:
    output = "5348";
    break;
  case SERIAL_NUM_LOW:
    output = "534C";
    break;
  case DEST_ADDR_HIGH:
    output = "4448";
    break;
  case DEST_ADDR_LOW:
    output = "444C";
    break;
  case TX_OPTIONS:
    output = "544F";
    break;
  case NODE_IDENTIFIER:
    output = "4E49";
    break;
  case NETWORK_DISC_BKOFF:
    output = "4E54";
    break;
  case DETWORK_DISC_OPT:
    output = "4E4F";
    break;
  case CLUSTER_ID:
    output = "4349";
    break;
  case NETWORK_DISC_TO:
    output = "4E3F";
    break;
  case ENCRYPTION_EN:
    output = "4545";
    break;
  case AES_ENCRYPTION_KEY:
    output = "4B59";
  case BAUD_RATE:
    output = "4244";
    break;
  case PARITY:
    output = "4E42";
    break;
  case STOP_BITS:
    output = "5342";
    break;
  case PACKET_TIMEOUT:
    output = "524F";
    break;
  case FLOW_CTRL_THRESHOLD:
    output = "4654";
    break;
  case API_ENABLE:
    output = "4150";
    break;
  case API_OPTIONS:
    output = "414F";
    break;
  case DIO_0_AD_0:
    output = "4430";
    break;
  case DIO_1_AD_1_SPI_ATTN:
    output = "4431";
    break;
  case DIO_2_AD_2_SPI_SCLK:
    output = "4432";
    break;
  case DIO_3_AD_3_SPI_SSEL:
    output = "4433";
    break;
  case DIO_4_SPI_MOSI:
    output = "4434";
    break;
  case DIO_5_ASSOC_IND:
    output = "4435";
    break;
  case DIO_6_RTS:
    output = "4436";
    break;
  case DIO_7_CTS:
    output = "4437";
    break;
  case DIO_8_SLEEP_REQ:
    output = "4438";
    break;
  case DIO_9_ON_SLEEP:
    output = "4439";
    break;
  case DIO_10_RSSI_PWM_0:
    output = "5030";
    break;
  case DIO_11_PWM_1:
    output = "5031";
    break;
  case DIO_12_SPI_MISO:
    output = "5032";
    break;
  case DIO_13_DOUT:
    output = "5033";
    break;
  case DIO_14_DIN:
    output = "5034";
    break;
  case PULL_DIRECTION:
    output = "5044";
    break;
  case PULL_UP_DWN_R_EN:
    output = "5052";
    break;
  case PWM_0_DUTY_CYCLE:
    output = "4D30";
    break;
  case PWM_1_DUTY_CYCLE:
    output = "4D31";
    break;
  case ASSOC_LED_BLINK_T:
    output = "4C54";
    break;
  case RSSI_PWM_TIMER:
    output = "5250";
    break;
  case ANALOG_V_REF:
    output = "4156";
    break;
  case DIO_CHANGE_DETECT:
    output = "4943";
    break;
  case SLEEP_SAMPLE_RATE:
    output = "4946";
    break;
  case SAMPLE_RATE:
    output = "4952";
    break;
  case TEMPERATURE:
    output = "5450";
    break;
  case SUPPLY_VOLTAGE:
    output = "2556";
    break;
  case SLEEP_MODE:
    output = "534D";
    break;
  case SLEEP_OPTIONS:
    output = "534F";
    break;
  case SLEEP_NUM_CYCLES:
    output = "534E";
    break;
  case SLEEP_TIME:
    output = "5350";
    break;
  case WAKE_TIME:
    output = "5354";
    break;
  case WAKE_HOST_DELAY:
    output = "5748";
    break;
  case SLEEP_STATUS:
    output = "5353";
    break;
  case OPERATING_SLEEP_T:
    output = "4F53";
    break;
  case OPERATING_WAKE_T:
    output = "4F57";
    break;
  case MISS_SYNC_MSGS:
    output = "4D53";
    break;
  case MISS_SLEEP_SYNC:
    output = "5351";
    break;
  case COMMAND_SEQ_CHAR:
    output = "4343";
    break;
  case COMMAND_MODE_TO:
    output = "4354";
    break;
  case GUARD_TIMES:
    output = "4754";
    break;
  case FIRMWARE_VERSION:
    output = "5652";
    break;
  case HARDWARE_VERSION:
    output = "4856";
    break;
  case HARDWARE_SERIES:
    output = "4853";
    break;
  case DEVICE_TYPE_ID:
    output = "4444";
    break;
  case MAX_PKT_PAYLOAD:
    output = "4E50";
    break;
  case CONFIG_CRC:
    output = "434B";
    break;
  case QUERIED_SAMPLING:
    output = "4953";
    break;
  }
  return output;
}

// Function to return the AT Command as an AT_type for switch chase
AT_type String_to_AT(String at_type)
{
  AT_type command = ERROR_AT;              // for return variable
  String at_value = Ascii_to_Hex(at_type); // conver the 2-character string into its 4-char hex value as string
  int at_int = String_to_Value(at_value);  // convert the string to an int

  // Switch case for possible int values and return AT_type -- added as needed
  switch (at_int)
  {
  case 0x4944:
  {
    command = NETWORK_ID;
    break;
  }
  case 0x4442:
  {
    command = LAST_PKT_RSSI;
    break;
  }
  case 0x5348:
  {
    command = SERIAL_NUM_HIGH;
    break;
  }
  case 0x534C:
  {
    command = SERIAL_NUM_LOW;
    break;
  }
  case 0x4448:
  {
    command = DEST_ADDR_HIGH;
    break;
  }
  case 0x444C:
  {
    command = DEST_ADDR_LOW;
    break;
  }
  case 0x4E49:
  {
    command = NODE_IDENTIFIER;
    break;
  }
  case 0x4349:
  {
    command = CLUSTER_ID;
    break;
  }
  case 0x4430:
  {
    command = DIO_0_AD_0;
    break;
  }
  case 0x4431:
  {
    command = DIO_1_AD_1_SPI_ATTN;
    break;
  }
  case 0x5450:
  {
    command = TEMPERATURE;
    break;
  }
  case 0x534D:
  {
    command = SLEEP_MODE;
    break;
  }
  case 0x534F:
  {
    command = SLEEP_OPTIONS;
    break;
  }
  case 0x534E:
  {
    command = SLEEP_NUM_CYCLES;
    break;
  }
  case 0x5350:
  {
    command = SLEEP_TIME;
    break;
  }
  case 0x5354:
  {
    command = WAKE_TIME;
    break;
  }
  case 0x5748:
  {
    command = WAKE_HOST_DELAY;
    break;
  }
  default:
  {
    command = ERROR_AT;
    break;
  }
  }
  return command;
}

/* *************************************************************************************
   Transmission Command Frames
 * ************************************************************************************/
// With the following functions, the string to be sent follows the format:
// START + frame_ID + length + data + checksum:
// START defined in header file
// frame_ID corresponding with the frame_ID sent with command
// length from function CreateLength in CreateFrame
// data from the subsequent functions depending the desired api frame type
// checksum from CheckSum

// AT Command
String AT_Command(String frame_ID, AT_type command, String data)
{
  String command_str = DefineATCommand(command);
  data = String(AT_CMD + frame_ID + command_str + data); // complete field of 'data' in the data frame
  data = CreateFrame(data);
  return data;
}

// Creating an AT Command Queue Command
String AT_Command_Queue(String frame_ID, AT_type command)
{
  String command_str = DefineATCommand(command);           // convert string inputs to the hex equivalents
  String data = String(AT_CMD_Q + frame_ID + command_str); // complete field of 'data' in the data frame
  data = CreateFrame(data);
  return data;
}

// Transmit Request Command
// Destination address can be specified or set to:
//   "0000000000000000" for the coordinator
//   "000000000000FFFF" for broadcast address
// Network address can be specified or set to:
//   "FFFE" if unknown or sending a broadcast
// Options can be set to:
//   "00" - No options
//   "01" - Disable retries and route repair
//   "20" - Enable APS encryption (if EE=1)
//   "40" - Use the extended transmission timeout -- NOTE: needed for sleeping end devices
String Transmit(String frame_ID, String dest_addr, String dest_network, String radius, String options, String data)
{
  data = Ascii_to_Hex(data); // convert input data to hex equivalent
  data = String(TRANSMIT + frame_ID + dest_addr + dest_network + radius + options + data);
  data = CreateFrame(data);
  return data;
}

// Explicit Address Command
// Destination address can be specified or set to:
//   "0000000000000000" for the coordinator
//   "000000000000FFFF" for broadcast address
// Network address can be specified or set to:
//   "FFFE" if unknown or sending a broadcast
// Options can be set to:
//   "00" - No options
//   "01" - Disable retries and route repair
//   "20" - Enable APS encryption (if EE=1)
//   "40" - Use the extended transmission timeout -- NOTE: needed for sleeping end devices
String ExplicitAddress(String frame_ID, String dest_addr, String dest_network, String src_end, String dest_end,
                       String cluster_ID, String profile_ID, String radius, String options, String data)
{

  data = String(EXPL_ADDR + frame_ID + dest_addr + dest_network + src_end + dest_end + cluster_ID + profile_ID + radius + options + data);
  data = CreateFrame(data);
  return data;
}

// Remote AT Command Request
// Destination address can be specified or set to:
//   "0000000000000000" for the coordinator
//   "000000000000FFFF" for broadcast address
// Network address can be specified or set to:
//   "FFFE" if unknown or sending a broadcast
// Options can be set to:
//   "01" - Disable retries and route repair
//   "02" - Apply changes - If not chosen, AC command needs to be sent before changes take effect
//   "20" - Enable APS Encryption
//   "40" - Use extended transmission timeout
String Remote_AT_Command(String frame_ID, String dest_addr, String dest_network, String options, AT_type command, String data)
{
  String command_str = DefineATCommand(command);
  data = String(REMOTE_AT + frame_ID + dest_addr + dest_network + options + command_str + data);
  data = CreateFrame(data);
  return data;
}

// Create Source Route
// Destination address can be specified or set to:
//   "0000000000000000" for the coordinator
//   "000000000000FFFF" for broadcast address
// Network address can be specified or set to:
//   "FFFE" if unknown or sending a broadcast
// Number Addresses in the source route (excluding source and destination)
// All Addresses to be in a single string starting with device closest to destination (eg. "AABBCC" - 3 devices, "AA" is closes to destination)
String SourceRoute(String frame_ID, String dest_addr, String dest_network, String num_addr, String all_addr)
{
  String data = String(SRC_ROUTE + frame_ID + dest_addr + dest_network + '0' + num_addr + all_addr);
  data = CreateFrame(data);
  return data;
}

/* *************************************************************************************
    Response Command Frames
 * ************************************************************************************/
// Function to return enum type from String to use in switch chase when parsing data
receive_type ReceiveAPI(int rx_api)
{
  receive_type api_type = ERROR_API;
  // Sort depending on value
  switch (rx_api)
  {
  case 0x88:
    api_type = AT_RESPONSE;
    break;
  case 0x8A:
    api_type = MDM_STATUS;
    break;
  case 0x8B:
    api_type = EXT_TX_STATUS;
    break;
  case 0x90:
    api_type = RX_PACKET;
    break;
  case 0x91:
    api_type = EXPL_RX_IND;
    break;
  case 0x92:
    api_type = IO_RX_IND;
    break;
  case 0x94:
    api_type = XBEE_SENSOR_READ;
    break;
  case 0x97:
    api_type = REMOTE_AT_RESPONSE;
    break;
  case 0x98:
    api_type = EXT_MDM_STATUS;
    break;
  case 0xA0:
    api_type = AIR_FW_UP_STATUS;
    break;
  case 0xA1:
    api_type = ROUTE_REC_IND;
    break;
  case 0xA3:
    api_type = MANY_ROUTE_REQ_IND;
    break;
  case 0xA5:
    api_type = JOIN_STATUS;
    break;
  default:
    Serial.print(F("Not recognized, value is: "));
    Serial.println(rx_api);
    break;
  }
  return api_type;
}
