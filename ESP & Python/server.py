'''

    "WARNING: Change only the config. Don't touch the code."
 __________________________________________________________________
|             |                  |                                 |
| TestRun = 1 | Calibration flag | To Check the socket connection  |
| TestRun = 0 | Handshake flag   | To stream the sensor data       |
|_____________|__________________|_________________________________|


'''

import socket

# Configs
BUFFER_SIZE = 1024
hostname = '0.0.0.0'
port = 5555
testRun = 0 # Flag

# Sockets
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((hostname, port))


# Function to send data to the client
def sendCommand(client, command):
    try:
        client.send(str(command))
    except Exception as e:
        return 1
    return 0



while True:
    try:
        data = s.recvfrom(BUFFER_SIZE)
        message = data[0].strip().decode()
        if(len(message)==0):
            break
        elif (message=="STARTUP"):
            print("STARTUP message received from ESP")
            if(testRun == 1):
                s.sendto(str.encode("CALIBRATION"), data[1])
                print("Calibration successful message sent to the ESP")
            elif(testRun == 0):
                s.sendto(str.encode("HANDSHAKE"), data[1])
                print("Handshake successful message sent to the ESP")
        elif (message=="Bye"):
            break
        else:
            print(message)
    except Exception as e:
        print("Exiting with Error", e)
        break
        
print("Closing the connection")
s.close()
