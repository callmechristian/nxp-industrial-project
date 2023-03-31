import cv2
import serial
import numpy as np
import matplotlib.pyplot as plt

# Initialize the serial port
ser = serial.Serial('COM3', 115200)

# Define the size of the image
width = 16
height = 1

while True:

    # Wait for an appropriate byte stream
    data = ser.readline()
    var = data.decode()
    res = var.replace("\n","")
    res = res.replace("\r","")
    res = res.replace("b","")
    list = res.split(",")

    # Read 128 values from the serial port
    # if(ser.readline()[0] == 'b'):
    
    # values = []
    # for i in range(128):
    #     values = list(ser.readline().decode())
    if len(list) > 1:
        values = []
        for i in range(len(list)):
            if list[i] != '':
                values.append(int(list[i]))
        values = np.array(values)
        print(values)
        # values = values.reshape(len(values), 1)
        # plt.imshow(values, cmap='gray', aspect='auto')
        # plt.show()
        # Reshape the array to a 2D array with a single row and multiple columns
        values = np.repeat(values, 5)
        img = np.tile(values, (100, 1))

        # Convert the data type of the image to CV_8U
        img8u = cv2.convertScaleAbs(img)
        
        # Display the image
        cv2.imshow('Image', img8u)
        
        # Add a delay to control the frame rate
        cv2.waitKey(1)
        
        # Check if the user pressed the 'q' key to exit the loop
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

# Close the window
cv2.destroyAllWindows()