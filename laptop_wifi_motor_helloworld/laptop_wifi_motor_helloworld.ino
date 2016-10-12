#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// !! Hardcoded Wireless Setup
const char* ssid = "DG1670AF2";
const char* password = "DG1670A6ACDF2";

const int speed = 0;

ESP8266WebServer server(80);

const int LED_PIN = D0;

const int MOTOR_PWM_LEFT = D1;
const int MOTOR_PWM_RIGHT = D2;

const int MOTOR_DIR_LEFT = D3;
const int MOTOR_DIR_RIGHT = D4;

#define MOTOR_CW LOW
#define MOTOR_CCW HIGH

void setup(void){
  // Setup motor and LED pins
  pinMode(MOTOR_PWM_LEFT, OUTPUT);
  pinMode(MOTOR_PWM_RIGHT, OUTPUT);
  pinMode(MOTOR_DIR_LEFT, OUTPUT);
  pinMode(MOTOR_DIR_RIGHT, OUTPUT);

  pinMode(LED_PIN, OUTPUT);

  // Set initial speed to 0
  analogWrite(MOTOR_PWM_LEFT, 0);
  analogWrite(MOTOR_PWM_RIGHT, 0);

  Serial.begin(115200);
  Serial.println("");

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
    String state = server.arg("state");
    analogWrite(MOTOR_PWM_LEFT, state.toInt());
    analogWrite(MOTOR_PWM_RIGHT, state.toInt());
    server.send(200, "text/plain", "Motor is now " + state);
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
