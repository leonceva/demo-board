// Definition of class Xbee
#ifndef Xbee_h
#define Xbee_h

#include "Frames.h"

// General Functions
String Ascii_to_Hex(String input);
short CharToHex(char character);
String CheckSum(String data);
String CreateLength(String data);
String CreateFrame(String data);
String CreateFrameID(int value);
int String_to_Value(String command);
String ReadIncomingData();
bool CheckStart(String first_byte);
String Hex_to_Ascii(String input);
String DefineATCommand(AT_type at_type);
AT_type String_to_AT(String at_type); // Missing cases, adding as needed -- GPIO: only pin 0,1 operational as of now

// Transmit APIs
String AT_Command(String frame_ID, AT_type command, String data);
String AT_Command_Queue(String frame_ID, AT_type command);
String Transmit(String frame_ID, String dest_addr, String dest_network, String radius, String options, String data);
String ExplicitAddress(String frame_ID, String dest_addr, String dest_network, String src_end, String dest_end, String cluster_ID, String profile_ID, String radius, String options, String data);
String Remote_AT_Command(String frame_ID, String dest_addr, String dest_network, String options, AT_type command, String data);
String SourceRoute(String frame_ID, String dest_addr, String dest_network, String num_addr, String all_addr);

// Receive APIs
receive_type ReceiveAPI(int rx_api);

#endif
