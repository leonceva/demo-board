#!/usr/bin/python3
from digi.xbee.devices import *

SENSOR_ADDRESS = "0013A20041BA172C"
USB_PORT = "/dev/ttyUSB0"

class DemoCommand:
    def __init__(self):
        self.instructions = ["GYRO", "POT", "SWITCH", "ALL"]
        self.command_unit = XBeeDevice(USB_PORT, 9600)
        self.sensor_unit = RemoteXBeeDevice(self.command_unit, XBee64BitAddress.from_hex_string(SENSOR_ADDRESS))

        try:
            self.command_unit.open()
        except:
            print("Unable to connect to the board (%s) in port (%s)" % (SENSOR_ADDRESS, USB_PORT))

        self.command_unit.add_data_received_callback(self.commandResponse)

    def sendCommand(self, selection):
        data = self.instructions[selection-1]
        response = self.command_unit.send_data(self.sensor_unit, data)
        return response

    def commandResponse(self, message):        
        receivedData = message.data.decode()
        print(receivedData)
        return receivedData

    def __del__(self):
        self.command_unit.close()
