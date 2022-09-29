#!/usr/bin/python3
from digi.xbee.devices import *

class DemoCommand:
    def __init__(self):
        self.instructions = ["GYRO", "POT", "SWITCH", "ALL"]
        self.command_unit = XBeeDevice("/dev/ttyUSB0", 9600)
        self.sensor_unit = RemoteXBeeDevice(self.command_unit, XBee64BitAddress.from_hex_string("0013A20041BA172C"))
        self.command_unit.open()
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
