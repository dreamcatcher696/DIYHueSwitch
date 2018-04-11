#include <ESP8266WiFi.h>

IPAddress switchip(192,168,0,2);  //give the esp an address, note lower out of dhcp range
IPAddress gateway(192,168,0,1);   //gateway of router
IPAddress subnet(255,255,255,0);  //subnet of router

const char hueBridgeIP[] = "192.168.0.110";   //bridge of the hue bridge, check at www.meethue.com/api/nupnp
const char hueUsername[] = "32T4xilFgfRRBYtcXirBNbKMwvoGlYR3j6dtjWcj"; //first create a registered user, and paste key here
const int hueHubPort = 80;  //always 80 ;)

const char ssid[] = "";//type your ssid
const char password[] = "";//type your password

WiFiClient client;

int butOnPin = 13;
int butOffPin = 12;



void setup() {
  pinMode(butOnPin,INPUT);
  pinMode(butOffPin,INPUT);
  Serial.begin(115200);
  delay(10);

  WiFi.config(switchip, gateway, subnet); 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
        Serial.println();
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(ssid);
        delay(500);
        Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void setHue(String command) 
  {
      if(client.connect(hueBridgeIP,hueHubPort))
      {
        client.print(String("PUT ") + "/api/32T4xilFgfRRBYtcXirBNbKMwvoGlYR3j6dtjWcj" + "/groups/1/action"\
        + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Content-Length: " + command.length() + "\r\n"\
        + "Content-Type: text/plain;charset=UTF-8\r\n\r\n" + command + "\r\n" + "Connection: close\r\n\r\n");
      }
    
  }
  
void loop() {
  if(digitalRead(butOnPin)==LOW)
  {
    Serial.println("button on pressed");
    String command =  "{\"on\": true}";
    setHue(command);
    int i = 0;  //counter for long presses
    while(digitalRead(butOnPin)==LOW && i < 30) {
      delay(20);
      i++;
    }
  }
  if(digitalRead(butOffPin)==LOW)
  {
    Serial.println("button off pressed");
    String command =  "{\"on\": false}";
    setHue(command);
    int i = 0;  //counter for long presses
    while(digitalRead(butOffPin)==LOW && i < 30) {
      delay(20);
      i++;
    }
  }
}
