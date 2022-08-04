import serial
import time
communication = serial.Serial(port='COM4', baudrate=9600, timeout=.1)

def sendData(x):
    communication.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
