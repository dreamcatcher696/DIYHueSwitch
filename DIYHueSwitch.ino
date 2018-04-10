#include <ESP8266Wifi.h>
#define DEBUG 1
//Define ip addresses
IPAddress switchip(192,168,0,2);  //give the esp an address, note lower out of dhcp range
IPAddress gateway(192,168,0,1);   //gateway of router
IPAddress subnet(255,255,255,0);  //subnet of router

int butOnPin    = 13;           //define the gpios on which the buttons are connected
int butHighPin  = 12;
int butLowPin   = 14;
int butOffPin   = 15;

int counter;


const char hueBridgeIP[] = "192.168.0.110";   //bridge of the hue bridge, check at www.meethue.com/api/nupnp
const char HueUsername = "32T4xilFgfRRBYtcXirBNbKMwvoGlYR3j6dtjWcj" //first create a registered user, and paste key here
const int hueHubPort = 80;  //always 80 ;)

const char ssid = "";//type your ssid
const char password = "";//type your password

WiFiClient client;  //create new client

void setup()
{
  if(DEBUG) //enalbe serial logging
  {
    Serial.begin(115200);
    delay(10);
  }
    WiFi.config(ip, gateway, subnet); 
    WiFi.begin(ssid, pass);
  
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
//declare the functions that get called on interrupt


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
    
