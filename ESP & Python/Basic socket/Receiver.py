import socket

# Configs
BUFFER_SIZE = 1024
hostname = '0.0.0.0'
port = 5555

# Sockets
s = socket.socket()
s.bind((hostname, port))
s.listen(0) # Simultaneous socket connections

client, address = s.accept()  # accept new connection
print("Connection from: client: " + str(address))
print("!!!")

while True:
    try:
        message = client.recv(BUFFER_SIZE)
        if(len(message)==0):
            break
        elif (message=="Bye"):
            break
        else:
            print(message)
    except Exception as e:
        print("Exiting with Error")
        client.close()
print("Closing connection")
client.close()