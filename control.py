from pythonosc import osc_message_builder
from pythonosc import udp_client
import serial
import sys
import time
from time import sleep

ser = serial.Serial('/dev/cu.usbserial-110', 9600)
sender = udp_client.SimpleUDPClient('127.0.0.1', 4559)

pitches = [60, 60, 60, 60]
vols = [0, 0, 0, 0]


def js_change(val):
    center = 2368  # values from 0 to 4095 but this joystick isn't perfectly calibrated
    change = center - val
    if change > 0:
        if change < 300:
            return 0
        if change < 1200:
            return 1
        else:
            return 2
    else:
        if change > -100:
            return 0
        if change > -1700:  # calibration problems
            return -1
        else:
            return -2


def vol(n, y):
    vols[n] += .05*y
    if vols[n] > 0.5:
        vols[n] = 0.5
    elif vols[n] < 0:
        vols[n] = 0
    sender.send_message('/vol', [n, vols[n]])


def pitch(n, y):
    pitches[n] += 0.25*y
    if pitches[n] > 100:
        pitches[n] = 100
    elif pitches[n] < 0:
        pitches[n] = 0
    sender.send_message('/pitch', [n, pitches[n]])


while True:
    try:
        ser_bytes = ser.readline()
        serialVal = str(ser_bytes, 'ascii').strip()
        serialVal = serialVal.split(' ')  # solo, voiceCurr, vfCurr, yVal
        values = []
        for i in range(0,4):
            values.append(int(serialVal[i]))
        y = js_change(values[3])
        if values[0] == 1:  # global volume mode
            for i in range(0,4):
                vol(i, y)
        else:
            if values[2] == 0:  # solo volume mode
                vol(values[1], y)
            else:  # solo pitch mode
                pitch(values[1], y)
        time.sleep(0.4)

    except:
        print(sys.exc_info()[0])
        break