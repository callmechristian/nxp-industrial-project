import serial
import time
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import animation

arduino = serial.Serial(port = 'COM4', baudrate=9600, timeout=0.1)

nx = 5
ny = 128

fig = plt.figure()
data = np.zeros((nx, ny))
im = plt.imshow(data, cmap='gist_gray_r', vmin=0, vmax=500)
image = np.random.rand(1, 128)


def init():
    im.set_data(image)

def animate(i):
   var='.'
   while True:
       var = arduino.readline().decode()
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
           xi = i // ny
           yi = i % ny
           data[xi, yi] = 1
           image = np.array([arrayRes])
           im.set_data(image)
           return im


anim = animation.FuncAnimation(fig, animate, init_func=init, frames=nx * ny, interval=5)
plt.show()
