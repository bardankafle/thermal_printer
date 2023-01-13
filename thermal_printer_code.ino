#include "Adafruit_Thermal.h" //runs with files in the adafruit thermal printer library
#include <ESP8266WiFi.h>
#include "SoftwareSerial.h"
#include <ESP8266WebServer.h>

#define TX_PIN D1 //labeled RX on printer
#define RX_PIN D2 //labeled TX on printer

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD"; 

ESP8266WebServer server(80);

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

void setup() {
  
  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  mySerial.begin(9600);  // Initialize SoftwareSerial
  Serial.begin(9600);
  
  // connect to wifi
  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected"); 
  Serial.print("IP Address of network: "); // will IP address on Serial Monitor
  Serial.println(WiFi.localIP());
  
  //start the web server
  server.begin();
  server.on("/", handleRoot); 
  server.onNotFound(handleNotFound);
  
  printer.begin();       // Init printer (same regardless of serial type)

}

void loop() {
  // keeping alert for post request from webpage
  server.handleClient();
  delay(1);
}

void handleNotFound() { 
  server.send(200, "text/html", getPage());
}

void handleRoot() { 
  if (server.args()) { 
    handleSubmit(); } 
  else { 
    server.send(200, "text/html", getPage()); 
  } 
}

String getPage() { 
  // webpage html code
  String page = "<!DOCTYPE HTML>"; 
  page += "<html>"; 
  page += "<head>"; 
  page += "<title>Bardan's Printer</title>";
  page += "</head>";
  page += "<body>";
  page += "<h1>Bardan's Printer</h1>";
  page += "<form action=\"/\" method=\"post\">";
  page += "Fill in the text you want to send";
  page += "<br><br>";
  page += "<textarea rows=\"5\" cols=\"50\" name='message' id=\"message\" value=\"printer\"></textarea>";
  page += "<br><br>";
  page += "<input type=\"submit\" value=\"Send to ESP\">";
  page += "</form>";
  page += "<br>";
  page += "<br>";
  page += "</body>";
  page += "</html>";
  
  return page;
}

void handleSubmit() { 
  //Text to show 
  if (server.hasArg("message")) { 
    String toSend_string = server.arg("message"); 
    Serial.print("The received text is:\n"); 
    Serial.println(toSend_string);
    Serial.print("Printing...");
    printer.println(toSend_string);
    
    //giving some space for tearing of printed page
    printer.println("");
    printer.println("");
    printer.println("");
    
    server.send(200, "text/html", getPage()); //Response to the HTTP request 
    }
}
