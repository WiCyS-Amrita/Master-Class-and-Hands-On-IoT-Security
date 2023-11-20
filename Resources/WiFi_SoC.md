# Master Class and Hands-On on IoT Security
![](https://img.shields.io/badge/Batch-22CYS-lightgreen) ![](https://img.shields.io/badge/Batch-21CYS-lightgreen) ![](https://img.shields.io/badge/UG-blue) ![](https://img.shields.io/badge/-CAM2023-blue) ![](https://img.shields.io/badge/-IOT01-gold)

Cyber Awareness Month - 2023: Master Class and Hands-On On IoT Security

## Code

```
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

const char* ssid     = "R1";      //enter your network ssid
const char* password = "raspberrypi";      //enter your network password
int led = 4;                    //onboard led
WiFiServer server(80);

void setup()
{
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
    Serial.begin(115200);
    pinMode(led, OUTPUT);      // set the LED pin mode

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
   
    server.begin();

}

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                            
    Serial.println("New Client.");          
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {            
        char c = client.read();            
        Serial.write(c);                  
        if (c == '\n') {                  


          if (currentLine.length() == 0) {

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 2 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 2 off.<br>");

            client.println();
            // break out of the while loop:
            break;
          } else {    
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(led, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(led, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
```
