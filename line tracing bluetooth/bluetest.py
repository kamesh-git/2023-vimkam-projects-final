import serial
import time


class arduino_bluetooth:
    def __init__(self):
        port = 'COM13'
        self.bluetooth = serial.Serial(port, 9600)
        self.bluetooth.flushInput()
        print("connected")

    def sendMsg(self,msg):
        self.bluetooth.write(str.encode(msg))#These need to be bytes not unicode, plus a number
        time.sleep(0.1)
        self.bluetooth.cancel_write()

