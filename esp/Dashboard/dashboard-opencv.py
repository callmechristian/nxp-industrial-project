'''

    "WARNING: Change only the config. Don't touch the code."
 __________________________________________________________________
|             |                  |                                 |
| TestRun = 1 | Calibration flag | To Check the socket connection  |
| TestRun = 0 | Handshake flag   | To stream the sensor data       |
|_____________|__________________|_________________________________|


'''

import socket

import serial
import time
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import animation

import cv2


# Configs
BUFFER_SIZE = 1024
hostname = '0.0.0.0'
port = 5555
testRun = 0 # Flag

# Sockets
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((hostname, port))

max_x = 128
thres = 5

img = np.zeros((200, max_x*thres, 3), np.uint8)
hist = np.zeros((200, max_x*thres, 3), np.uint8)

count = 0

while True:
    try:
        data = s.recvfrom(BUFFER_SIZE)
        message = data[0].decode(errors='ignore').strip()
        # message = data[0].strip().decode()
        if(len(message)==0):
            break
        elif (message=="STARTUP"):
            if(testRun == 1):
                s.sendto(str.encode("CALIBRATION"), data[1])
                print("Calibration successful message sent to the ESP")
            elif(testRun == 0):
                s.sendto(str.encode("HANDSHAKE"), data[1])
                # time.sleep(1)
                print("Handshake successful message sent to the ESP")
        elif (message=="Bye"):
            print("Closing the connection")
            s.close()
            break
        else:
            count+=1
            try:
                values = [int(x) for x in message.split(',') if x!=""]
                # print("Data count: ", count, "| Message length: ", len(message), "| Number of pixels: ", len(values))
                # print(message)
                values = values[0:128]
                hist = np.roll(hist, 1, axis=0) # shift the histogram up by one row
                hist[0:199, :, :] = 0 # clear the first row of the histogram
                for i, value in enumerate(values):
                    hist[0:199, i*thres, 1] = value # set the blue channel value of the first row to the value received from the Arduino
                cv2.imshow('Camera Visualisation', hist)
                cv2.waitKey(1)
            except:
                pass

    except Exception as e:
        print("Exiting with Error: ", e)
        break
    