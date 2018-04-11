#include <ESP8266WiFi.h>
#define DEBUG 1
//Define ip addresses
IPAddress switchip(192,168,0,2);  //give the esp an address, note lower out of dhcp range
IPAddress gateway(192,168,0,1);   //gateway of router
IPAddress subnet(255,255,255,0);  //subnet of router

int butOnPin    = 13;           //define the gpios on which the buttons are connected
int butHighPin  = 12;
int butLowPin   = 14;
int butOffPin   = 15;

int group = 1;

int counter;


const char hueBridgeIP[] = "192.168.0.110";   //bridge of the hue bridge, check at www.meethue.com/api/nupnp
const char hueUsername[] = "32T4xilFgfRRBYtcXirBNbKMwvoGlYR3j6dtjWcj"; //first create a registered user, and paste key here
const int hueHubPort = 80;  //always 80 ;)

const char ssid[] = "";//type your ssid
const char password[] = "";//type your password

WiFiClient client;  //create new client

void setup()
{
  pinMode(butOnPin,INPUT);
  pinMode(butHighPin,INPUT);
  pinMode(butLowPin,INPUT);
  pinMode(butOffPin,INPUT);
  if(DEBUG) //enalbe serial logging
  {
    Serial.begin(115200);
    delay(10);
  }
    WiFi.config(switchip, gateway, subnet); 
    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) 
    {
      if(DEBUG)
      {
        Serial.println();
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(ssid);
        delay(500);
        Serial.print(".");
      }
      delay(1);
    }
    if(DEBUG)
    {
      Serial.println("");
      Serial.println("WiFi connected");
    }
    
}
void setHue(String command) 
  {
    if (client.connect(hueBridgeIP, hueHubPort))
     {
        client.print("PUT /api/");
        client.print(hueUsername);
        client.print("/groups/"); 
        client.print(group);
        client.print("/action"); 
        client.println("/state HTTP/1.1");
        client.println("keep-alive");
        client.print("Host: ");
        client.println(hueBridgeIP);
        client.print("Content-Length: ");
        client.println(command.length());
        client.println("Content-Type: text/plain;charset=UTF-8");
        client.println();  // blank line before body
        client.println(command);
        client.stop(); 
      }
  }


void loop()
{
  if(digitalRead(butOnPin)== HIGH )
  {
    if(DEBUG)
    {
      Serial.println("");
      Serial.println("button on pressed");
    }
    //do something
    String command = "{\"on\":true}";
    setHue(command);
    counter = 0;
    int i = 0;  //counter for long presses
    while(digitalRead(butOnPin)==HIGH && i < 30) {
      delay(20);
      i++;
    }
  }
  if(digitalRead(butHighPin)==HIGH)
  {
    counter = 0;
    int i = 0;  //counter for long presses
    while(digitalRead(butHighPin)==HIGH && i < 30) {
      delay(20);
      i++;
    }
    if(i<30)
    {
      if(DEBUG)
      {
        Serial.println("");
        Serial.println("button  high pressed(short)");
      }
      //do something
      String command = "{\"on\": true,\"bri\": 204,\"hue\": 1876,\"sat\": 254}";
      setHue(command);
    }
    else 
    {
      if(DEBUG)
      {
        Serial.println("");
        Serial.println("button  high pressed(long)");
      }      
      //do something, long press
    }
  }
  if(digitalRead(butLowPin)==HIGH)
  {
    counter = 0;
    int i = 0;  //counter for long presses
    while(digitalRead(butLowPin)==HIGH && i < 30) {
      delay(20);
      i++;
    }
    if(i<30)
    {
      if(DEBUG)
      {
        Serial.println("");
        Serial.println("button  low pressed(short)");
      }
      //do something
    }
    else 
    {
      if(DEBUG)
      {
        Serial.println("");
        Serial.println("button  low pressed(long)");
      }      
      //do something, long press
    }
  }
  if(digitalRead(butOffPin)== HIGH )
  {
    if(DEBUG)
    {
      Serial.println("");
      Serial.println("button on pressed");
    }
    //do something
    String command = "{\"on\":false}";
    setHue(command);
    counter = 0;
    int i = 0;  //counter for long presses
    while(digitalRead(butOffPin)==HIGH && i < 30) {
      delay(20);
      i++;
    }
  }
  if(counter==5000)
  {
    yield();
    delay(100);
    ESP.deepSleep(0);
    yield();
  }
  else
  {
    counter++;
  }
}
    
