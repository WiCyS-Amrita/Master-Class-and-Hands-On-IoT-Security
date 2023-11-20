#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "Team-16";   
const char* password = "12345678";  

WiFiClient  client;

unsigned long myChannelNumber = 2351385;
const char * myWriteAPIKey = "Y2I8SQ7RMUOKUOT3";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

// Variable to hold temperature readings
float temperatureC=22.0;


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

    temperatureC = analogRead(39); 
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