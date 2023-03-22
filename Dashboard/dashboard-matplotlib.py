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


# Configs
BUFFER_SIZE = 1024
hostname = '0.0.0.0'
port = 5555
testRun = 0 # Flag

# Sockets
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((hostname, port))

# Visualisation Config
nx = 5
ny = 128

fig = plt.figure()
data = np.zeros((nx, ny))
im = plt.imshow(data, cmap='gist_gray_r', vmin=0, vmax=4000)
image = np.random.rand(1, 128)

# Visualisation functions



def init():
    im.set_data(image)

def animate(i):
   var=''
   while True:
        data = s.recvfrom(BUFFER_SIZE)
        var = data[0].strip().decode(errors='ignore')
        var = var[1:-2]
        res = var.replace("\n","")
        res = res.replace("\r","")
        res = res.replace("b","")
        list = res.split(",")
            
        if len(list)>1:
            list = list[:len(list)-2]
            arrayRes=[]
            for el in list:
                if el!= '':
                    arrayRes.append(int(el))
            #print ("\nand list is :", arrayRes)
            image = np.array([arrayRes])
            im.set_data(image)
            return im


# Function to send data to the client
def sendCommand(client, command):
    try:
        client.send(str(command))
    except Exception as e:
        return 1
    return 0

anim = animation.FuncAnimation(fig, animate, init_func=init, frames=nx * ny, interval=5)
plt.show()