/*
  Wireless LED -- Access Point Wireless Mode

  Turn an LED on and off wirelessly.
  ESP creates a wireless network with SSID "ESP8266 Thing" and password "sparkfun".
  Connect a smartphone to that network. On the phone's browser, go to 192.168.4.1/led/0 or /led/1
  
  Hardware: 
  * NodeMCU Amica DevKit Board (ESP8266 chip)

  Source: https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/example-sketch-ap-web-server
  * Changed LED pin from 5 to D0 (GPIO5 is D1 which does not connect to LED on my board)
  * Added {} to if statements so code less likely to function unexpectedly with no erros thrown when you add another line to the if statement
  * Added a lot of Serial printlns for debugging
  * Renamed APPSK[] to password[] for readability
  * LED turns ON when writing 0 to LED pin, changed HTML to reflect this

  modified Nov 2016
  by Nancy Ouyang
*/


#include <ESP8266WiFi.h>

//////////////////////
// WiFi Definitions //
//////////////////////
const char password[] = "sparkfun";

/////////////////////
// Pin Definitions //
/////////////////////
const int LED_PIN = D4; // Thing's onboard, blue LED. Also sets CW/CCW direction for right motor

WiFiServer server(80);

void setup() 
{
  initHardware();
  Serial.println("Serial up and running");
  setupWiFi();
  server.begin();
}

void loop() 
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("Client connected!");
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int val = -1; // We'll use 'val' to keep track of both the
                // request type (read/set) and value if set.
                
  if (req.indexOf("/led/0") != -1) {
    Serial.println("LED on request received");
    val = 0; // Will write LED low
  }
  
  if (req.indexOf("/led/1") != -1) {
    Serial.println("LED off request received");
    val = 1; // Will write LED high
  }
    
  // Otherwise request will be invalid. We'll say as much in HTML

  // Set D0 according to the request
  if (val >= 0) {
    digitalWrite(LED_PIN, val);
    Serial.println("LED PIN value set to...");
    Serial.println(val);
  }

  client.flush();

  // Prepare the response. Start with the common header:
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  
  // If we're setting the LED, print out a message saying we did
  if (val >= 0)  {
    s += "LED is now ";
    s += (val)?"off":"on";
  }
  else  {
    s += "Invalid Request.<br> Try /led/1 or /led/0.";
  }
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disconnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}


/////////////////////
//      Setup      //
/////////////////////

void setupWiFi()
{
  //Set the mode to AP for Access Point, as opposed to ST for station
  //ESP acts as an Access Point so other devices can caonnect ot it 
  //Otherwise, in Station Mode, ESP acts as a device and connects to existing access point
  WiFi.mode(WIFI_AP);

  // SSID
  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ESP8266 Thing " + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, password);
}

void initHardware()
{
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); //LED should be on at beginning
}

