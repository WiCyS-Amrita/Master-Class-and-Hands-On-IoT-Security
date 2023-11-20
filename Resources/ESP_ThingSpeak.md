# Master Class and Hands-On on IoT Security
![](https://img.shields.io/badge/Batch-22CYS-lightgreen) ![](https://img.shields.io/badge/Batch-21CYS-lightgreen) ![](https://img.shields.io/badge/UG-blue) ![](https://img.shields.io/badge/-CAM2023-blue) ![](https://img.shields.io/badge/-IOT01-gold)

Cyber Awareness Month - 2023: Master Class and Hands-On On IoT Security

## Code
```
#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "SDPK -LBS POOJAPPURA";   
const char* password = "Sdpk@123";  

WiFiClient  client;

unsigned long myChannelNumber = 1830052;
const char * myWriteAPIKey = "DAJ35CEQ078Y5B6X";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

// Variable to hold temperature readings
float temperatureC=10.0;


// Create a sensor object


void setup() {
  Serial.begin(115200);  //Initialize serial
 
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    temperatureC = analogRead(36); 
    Serial.print("Temperature (ºC): ");
    Serial.println(temperatureC);
    

    Serial.print("Temperature (ºC): ");

    
    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 1, temperatureC, myWriteAPIKey);
    //uncomment if you want to get temperature in Fahrenheit
    //int x = ThingSpeak.writeField(myChannelNumber, 1, temperatureF, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    delay(15000);
    lastTime = millis();
  }
}
```
