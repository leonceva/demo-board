#!/usr/bin/python3
from digi.xbee.devices import *
from datetime import datetime

SENSOR_ADDRESS = "0013A20041BA172C"
USB_PORT = "/dev/ttyUSB1"

class DemoCommand:
    def __init__(self):
        self.instructions = ["GYRO", "POT", "SWITCH", "ALL"]
        self.command_unit = XBeeDevice(USB_PORT, 9600)
        self.sensor_unit = RemoteXBeeDevice(self.command_unit, XBee64BitAddress.from_hex_string(SENSOR_ADDRESS))
        self._last_data = None
        self.data_flag = False
        self._command_timeout = 10
        try:
            self.command_unit.open()
        except:
            print("Unable to connect to the board (%s) in port (%s)" % (SENSOR_ADDRESS, USB_PORT))
        self.command_unit.add_data_received_callback(self.commandResponse)

    def sendCommand(self, selection):
        data = self.instructions[selection]
        try:
            print("Sending Command: %s" % self.instructions[selection])
            response = self.command_unit.send_data(self.sensor_unit, data)
        except Exception as e:
            print(e)
            return("FAILED")

        print(response.transmit_status)
        if(response.transmit_status == TransmitStatus.SUCCESS):
            return True
        else:
            return False

    def commandResponse(self, message):        
        receivedData = message.data.decode()
        self._last_data = receivedData
        self.data_flag = True

    def getGyroData(self):
        print("Getting Gyroscope Data")
        sendGyro = self.sendCommand(0)
        if (sendGyro == True):
            print("Waiting on response..")
            timer_start = datetime.now()
            while(self.data_flag == False):
                time_delta = datetime.now() - timer_start
                if (time_delta.total_seconds() >= self._command_timeout):
                    print("Did not receive data - TIMEOUT")
                    return("TIMEOUT")
                else:
                    continue
            print("Received data: %s" % self._last_data)
            self.data_flag = False
            return(self._last_data)
        else:
            print("Transmit Failure - FAILED")
            return("FAILED")

    def getPotData(self):
        print("Getting Potentiometer Data")
        sendGyro = self.sendCommand(1)
        if (sendGyro == True):
            print("Waiting on response..")
            timer_start = datetime.now()
            while(self.data_flag == False):
                time_delta = datetime.now() - timer_start
                if (time_delta.total_seconds() >= self._command_timeout):
                    print("Did not receive data - TIMEOUT")
                    return("TIMEOUT")
                else:
                    continue
            print("Received data: %s" % self._last_data)
            self.data_flag = False
            return(self._last_data)
        else:
            print("Transmit Failure - FAILED")
            return("FAILED")

    def getSwitchData(self):
        print("Getting Switch Status")
        sendGyro = self.sendCommand(2)
        if (sendGyro == True):
            print("Waiting on response..")
            timer_start = datetime.now()
            while(self.data_flag == False):
                time_delta = datetime.now() - timer_start
                if (time_delta.total_seconds() >= self._command_timeout):
                    print("Did not receive data - TIMEOUT")
                    return("TIMEOUT")
                else:
                    continue
            print("Received data: %s" % self._last_data)
            self.data_flag = False
            return(self._last_data)
        else:
            print("Transmit Failure - FAILED")
            return("FAILED")

    def getAllData(self):
        print("Getting All Sensor Data")
        sendGyro = self.sendCommand(3)
        if (sendGyro == True):
            print("Waiting on response..")
            timer_start = datetime.now()
            while(self.data_flag == False):
                time_delta = datetime.now() - timer_start
                if (time_delta.total_seconds() >= self._command_timeout):
                    print("Did not receive data - TIMEOUT")
                    return("TIMEOUT")
                else:
                    continue
            print("Received data: %s" % self._last_data)
            self.data_flag = False
            return(self._last_data)
        else:
            print("Transmit Failure - FAILED")
            return("FAILED")

    def __del__(self):
        self.command_unit.close()

# Uncomment section below if wanting to use as a standalone terminal script
"""
if __name__ == '__main__':
    demo_board = DemoCommand()
    while(1): 
        try:       
            data = demo_board.getAllData()
            print("%s" % data)
            time.sleep(5)
        except Exception as e:
            print(e)
            del demo_board
            break
"""