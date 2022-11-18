#include <WiFi.h>

//const char* ssid = "xhr1s";
//const char* password = "TURRRRBO";
//const char * host = "169.254.11.74";

const char* ssid = "RoosterRalph";
const char* password = "2345678901";
const char * host = "192.168.43.77";

const uint16_t port = 5555;

unsigned long previousMillis = 0;
unsigned long interval = 7000;

WiFiClient client;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}


void setup()
{
  Serial.begin(115200);
  initWiFi();
  
  if (!client.connect(host, port)) {
    Serial.println("Connection to host failed");
    delay(1000);
    return;
  }
  else {
    Serial.print("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());
  }
}

void loop()
{
  
  Serial.println("Start over");
  for(int i=0;i<10;i++){
    client.println("Hello from ESP32!");
    delay(500);
  }
  client.print("Bye");
  Serial.println("Disconnecting...");
  client.stop();
  delay(100000000);
}
