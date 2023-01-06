# Import packages
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
from math import pi
import time

import serial

# Import animation package
from matplotlib.animation import FuncAnimation


ser = serial.Serial('COM6', 115200, timeout=0)

# creating subplot and figure
fig = plt.figure()
ax = fig.add_subplot(111)
hl, = ax.plot([], [])

# all data packages have 127 values
x = np.linspace(0, 127, 127)

# setting labels
plt.xlabel("128 Pixel Array")
plt.ylabel("Values 0 - 255")
plt.title("Linescan camera feed")

plt.ion()


def update_line(hl, new_data):
    hl.set_xdata(x)
    hl.set_ydata(new_data)
    # plt.draw()
    

while True:
  line = ser.readline().decode()
  if(line):
    data = line.strip()

    data = data.split(",")
    data = data[:len(data)-2]
    print(data)
    for i in range(0,len(data)):
        data[i] = int(data[i])

    update_line(hl, data)
    
    print("Updated.")
    fig.canvas.draw()
  # print(data)
# time.sleep(2)

# generating random data values
# x = np.linspace(0, 127, 127)
# y = np.random.randint(0, 255, 127)

# enable interactive mode
# plt.ion()

# creating subplot and figure
# fig = plt.figure()
# ax = fig.add_subplot(111)
# line1, = ax.plot(x, y)

# # setting labels
# plt.xlabel("128 Pixel Array")
# plt.ylabel("Values 0 - 255")
# plt.title("Linescan camera feed")

# count = 10

# looping
# while True:
#   line = ser.readline()   # read in bytes
#   if(line):
#     data = line.decode().strip()
#     try:
#       datalist = data.split(",")
#       datalist = (datalist[:len(datalist)-2])
#       datalist_str = datalist
#       for i in range(0,len(datalist_str)):
#         datalist_str[i] = int(datalist_str[i])
#       # print(len(datalist_str), " == 127")
#       # print(datalist_str)
#       # time.sleep(1)
#       if(len(datalist_str) == 127):
#         # count = count - 1
#         # print(len(datalist_str))
#         # updating the value of x and y
#         line1.set_xdata(x)
#         line1.set_ydata(datalist_str)
#         # re-drawing the figure
#         fig.canvas.draw()
#         # to flush the GUI events
#         fig.canvas.flush_events()
#         # print("***********************************************************")
#     except Exception as e:
#       pass
  # time.sleep(0.1)
