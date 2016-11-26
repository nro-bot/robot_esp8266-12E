/*
  Wireless Motor -- Station Wireless Mode

  Set speed of both motors wirelessly.

  Station mode means we can remain connected to the internet on our normal wifi connection
  and interact with the ESP at the same time (vs AP mode, where we connect to the ESP only).

  Usage:
    Put in the code below the SSID and password for your existing wifi connection that we will connect the ESP to.
    Compile and upload.

    On a laptop connected to the same wireless network, open up a browser.
    Go to the IP address which shows up in the serial monitor, e.g.
        IP address: 192.168.0.10
    and you should see "hello from esp8266!"

    Set speed with: 192.168.0.10/motor?speed=800

  Notes: 
  * One of the motor pins overlaps with LED pin D4, so when the left wheel is going CW, the LED light close the ESP chip will turn on
  * We opted to swap the motor wires on the right motor so that LOW is backwards for both motors
  * We arbitrarily define left motor CW = backwards

  Hardware: 
  * NodeMCU Amica DevKit Board (ESP8266 chip)
  * Motorshield for NodeMCU 
  * 2 motors + 2 wheels + motor chassis with caster
  * Left motor connected to D3 (BLK/A- and RED/A+ on the shield)
  * Right motor connected to D4, with wires swapped (RED/B- and BLK/B+ on the shield)w

  modified Nov 2016
  by Nancy Ouyang
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// !! Hardcoded Wireless Setup
const char* ssid = "......";
const char* password = "......";

const int speed = 0;

ESP8266WebServer server(80);

const int LED_PIN = D0;

const int MOTOR_PWM_LEFT = D1;
const int MOTOR_PWM_RIGHT = D2;

const int MOTOR_DIR_LEFT = D3;
const int MOTOR_DIR_RIGHT = D4;

#define MOTOR_BACK LOW
#define MOTOR_FWD HIGH


void setup(void){
  // Setup motor and LED pins
  pinMode(MOTOR_PWM_LEFT, OUTPUT);
  pinMode(MOTOR_DIR_LEFT, OUTPUT);
  pinMode(MOTOR_PWM_RIGHT, OUTPUT);
  pinMode(MOTOR_DIR_RIGHT, OUTPUT);

  pinMode(LED_PIN, OUTPUT);

  // Set initial speed to 0
  analogWrite(MOTOR_PWM_LEFT, 0);
  analogWrite(MOTOR_PWM_RIGHT, 0);

  Serial.begin(115200);
  Serial.println("Hello~");

  // Set up WIFI
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  //
  // Handle URLs
  //

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/motor", [](){
    String speed = server.arg("speed");
    
    digitalWrite(MOTOR_DIR_LEFT, MOTOR_FWD);
    digitalWrite(MOTOR_DIR_LEFT, MOTOR_BACK);

    analogWrite(MOTOR_PWM_LEFT, speed.toInt());
    analogWrite(MOTOR_PWM_RIGHT, speed.toInt());
    
    server.send(200, "text/plain", "Motor is now " + speed);
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}


void loop(void){
  server.handleClient();
}



void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}


void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  delay(1000);
}
