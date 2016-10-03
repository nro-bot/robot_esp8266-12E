/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  modified 8 May 2014
  by Scott Fitzgerald
*/

#include <ESP8266WiFi.h>

#define right_cw HIGH 
#define right_ccw LOW
#define left_cw LOW 
#define left_ccw HIGH 

#define motor_pwm_left D1
#define motor_pwm_right D2

#define motor_dir_left D3
#define motor_dir_right D4

int speed_left = 1000;
int speed_right = 1000;

//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPPSK[] = "sparkfun";
  
/////////////////////
// Pin Definitions //
/////////////////////
const int LED_PIN = D0; // Thing's onboard, green LED
const int ANALOG_PIN = A0; // The only analog pin on the Thing
const int DIGITAL_PIN = 12; // Digital pin to be read

//const int MOTOR_PWM_LEFT = D1;
//const int MOTOR_DIR_LEFT = D3; 


WiFiServer server(80);

void setup() 
{
  initHardware();
  setupWiFi();
  server.begin();

  pinMode(motor_dir_left, OUTPUT);
  pinMode(motor_dir_right, OUTPUT);
  pinMode(motor_pwm_left, OUTPUT);
  pinMode(motor_pwm_right, OUTPUT);
}

void loop() 
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int val = -1; // We'll use 'val' to keep track of both the
                // request type (read/set) and value if set.

  int mval = -1;


  if (req.indexOf("/l/0") != -1)
    val = 0; // Will write LED low

  else if (req.indexOf("/l/1") != -1)
    val = 1; // Will write LED high

  // set motor direction (forward or backward)
  else if (req.indexOf("/m/0") != -1) {
    digitalWrite(motor_dir_left, left_cw);
    mval = 999;
  }
    
  else if (req.indexOf("/m/1") != -1) {
    digitalWrite(motor_dir_left, left_ccw);
    mval = 0;
  }

  else if (req.indexOf("/r") != -1)
    val = -2; // Will print pin reads
  // Otherwise request will be invalid. We'll say as much in HTML

  // Set GPIO5 according to the request
  else if (val >= 0)
    digitalWrite(LED_PIN, val);

  // set motor speed
  else if (mval >= 0)
    analogWrite(motor_pwm_left, speed_left);
    //digitalWrite(MOTOR_LEFT_PIN, val);

  client.flush();

  // Prepare the response. Start with the common header:
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  // If we're setting the LED, print out a message saying we did

  String ms = "";

  if (val >= 0)
  {
    s += "LED is now ";
    s += (val)?"on":"off";
  }

  // motor functions
  else if (mval = 0)
  {
    ms += "left motor is now turning backward (ccw)";
  }
  else if (mval > 0)
  {
    ms += "left motor is now turning forward (cw)";
  }


  else if (val == -2)
  { // If we're reading pins, print out those values:
    s += "Analog Pin = ";
    s += String(analogRead(ANALOG_PIN));
    s += "<br>"; // Go to the next line.
    s += "Digital Pin 12 = ";
    s += String(digitalRead(DIGITAL_PIN));
  }
  else
  {
    s += "Invalid Request.<br> Try /l/1, /l/0, /m/1, /m/0, or /r.";
  }
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  client.print(ms);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

void setupWiFi()
{
  WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "TEST ESP826 " + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}

void initHardware()
{
  Serial.begin(115200);
  pinMode(DIGITAL_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  // Don't need to set ANALOG_PIN as input, 
  // that's all it can be.
}

