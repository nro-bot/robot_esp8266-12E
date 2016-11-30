// Station Mode -- connect me to a wireless network!
#include "ESP8266WiFi.h"
#include <aREST.h>
#include <Wire.h>

const int LED_PIN = D0;

const int MOTOR_PWM_LEFT = D1;
const int MOTOR_PWM_RIGHT = D2;

const int MOTOR_DIR_LEFT = D3;
const int MOTOR_DIR_RIGHT = D4;

#define MOTOR_BACK LOW
#define MOTOR_FWD HIGH


// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "......";
const char* password = "......";

// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Function
int stop(String message);
int forward(String message);
int right(String message);
int left(String message);
int backward(String message);

void setup(void)
{  
  pinMode(MOTOR_PWM_LEFT, OUTPUT);
  pinMode(MOTOR_DIR_LEFT, OUTPUT);
  pinMode(MOTOR_PWM_RIGHT, OUTPUT);
  pinMode(MOTOR_DIR_RIGHT, OUTPUT);

  pinMode(LED_PIN, OUTPUT);

  // Set initial speed to 0
  analogWrite(MOTOR_PWM_LEFT, 0);
  analogWrite(MOTOR_PWM_RIGHT, 0);

  // Start Serial
  Serial.begin(115200);

  // Functions          
  rest.function("stop", stop);
  rest.function("forward", forward);
  rest.function("left", left);
  rest.function("right", right);
  rest.function("backward", backward);
      
  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("robot");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.println(WiFi.localIP());
  
}

void loop() {
  
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
 
}

int stop(String command) {
  analogWrite(MOTOR_PWM_LEFT, 0);
  analogWrite(MOTOR_PWM_RIGHT, 0);
}

int forward(String command) {
  digitalWrite(MOTOR_DIR_LEFT, MOTOR_FWD);
  digitalWrite(MOTOR_DIR_RIGHT, MOTOR_FWD);

  analogWrite(MOTOR_PWM_LEFT, 800);
  analogWrite(MOTOR_PWM_RIGHT, 800);
}

int left(String command) {
  digitalWrite(MOTOR_DIR_LEFT, MOTOR_BACK);
  digitalWrite(MOTOR_DIR_RIGHT, MOTOR_FWD);

  analogWrite(MOTOR_PWM_LEFT, 800);
  analogWrite(MOTOR_PWM_RIGHT, 800);
}

int right(String command) {
  digitalWrite(MOTOR_DIR_LEFT, MOTOR_FWD);
  digitalWrite(MOTOR_DIR_RIGHT, MOTOR_BACK);

  analogWrite(MOTOR_PWM_LEFT, 800);
  analogWrite(MOTOR_PWM_RIGHT, 800);
}

int backward(String command) {
  digitalWrite(MOTOR_DIR_LEFT, MOTOR_BACK);
  digitalWrite(MOTOR_DIR_RIGHT, MOTOR_BACK);

  analogWrite(MOTOR_PWM_LEFT, 800);
  analogWrite(MOTOR_PWM_RIGHT, 800);
}
