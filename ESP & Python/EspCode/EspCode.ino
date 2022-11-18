/*

WARNING: Change only the config. Don't touch the code.
 ____________________________________________________
|                  |                                 |
| Calibration flag | To Check the socket connection  |
| Handshake flag   | To stream the sensor data       |
|__________________|_________________________________|

Install NTPClient library. Sketch => Include libraries => Manage libraries.

Make sure the ESP and the Computer are connected to the same network.
Check the computer's IP format is IPV4 after connecting to the network.

Connections:
First flash the codes to the NXP and the ESP board.
Then connect TX pin of the NXP to the RX pin of the ESP.
Common connect the ground pins of both the boards.
If you flash the codes after connecting this connection, there will be errors.
 ________________________
|           |            |
| NXP Board | ESP Board  |
|___________|____________|
|           |            |
| TX Pin    | RX Pin     |
| Gnd Pin   | Gnd Pin    |
|___________|____________|

NXP to ESP => Serial communication
Whatever you print in nxp will be read as string from the ESP.
So print all the necessary data as a single line seperated by ',' or '|'.

ESP to Computer(Python) => UDP Sockets
When you reset the ESP, Startup signal will be sent to the python server.
From the server, either calibration flag or handshake flag will be sent back based on config.
If it is Calibration flag, a hardcoded message will be sent to the server with 1sec delay for 10 times and ends.
If it is Handshake flag, the serially read data will be sent to the server (If available).

*/

#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

/* Configs starts here */
const char * ssid = "RoosterRalph";
const char * password = "2345678901";
const char * ipAddress = "192.168.43.77"; // IpAddress of the PC
const long utcOffsetInSeconds = 3600;
const int port = 5555;
/* Configs ends here */

int state = 0;
String timestamp = "";
uint8_t buffer[50];
String msg = "";
String SerialData = "";
int count = 0;

//create UDP instance
WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org", utcOffsetInSeconds);

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("|\nWiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}


void UdpSend(String message){
      Serial.print("Data: ");
      Serial.println(message);
      udp.beginPacket(ipAddress, port);
      udp.print(message.c_str());
      udp.endPacket();
}

void setup(){
  Serial.begin(115200);
  initWiFi();
}

void loop(){
  
  timeClient.update();
  timestamp = String(timeClient.getFormattedTime());

  //data will be sent to server
  if(state == 0){
    UdpSend("STARTUP");
    udp.parsePacket();
    //receive response from server
    if(udp.read(buffer, 50) > 0){
      Serial.print("Server to client: ");
      String flag = (char *)buffer;
      Serial.println(flag);
      if(flag == "CALIBRATION"){
        state = 1;
        Serial.println("Calibration successful | State 1 assigned successfully");
      }else if(flag == "HANDSHAKE"){
        state = 2;
        Serial.println("Handshake successful | State 2 assigned successfully");
      }
    }
  }else if(state == 1){
    msg = timestamp + " | Calibration Data | Socket test successful";
    UdpSend(msg);
    count = count + 1;
    delay(1000);
  }else if(state == 2){
    if (Serial.available() > 0) {                 // UART Protocol
      SerialData = Serial.readStringUntil('\n');
    }
    msg = timestamp + " | " + SerialData;
    UdpSend(msg);
  }

  if(count == 10){
    count = 0;
    UdpSend("Bye");
    Serial.println("Closing the connection");
    delay(3600000);
  }
}
