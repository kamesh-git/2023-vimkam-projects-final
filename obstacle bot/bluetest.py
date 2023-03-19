import serial
import time


class arduino_bluetooth:
    def __init__(self):
        port = 'COM10'
        self.bluetooth = serial.Serial(port, 9600)
        self.bluetooth.flushInput()

    def sendMsg(self,msg):
        self.bluetooth.write(str.encode(msg))#These need to be bytes not unicode, plus a number
        time.sleep(0.1)

