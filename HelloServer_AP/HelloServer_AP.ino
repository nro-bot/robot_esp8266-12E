/* 
 AP Mode, Hello World Example
 Source: https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/example-sketch-ap-web-server
 Put in the ssid and password for the wifi connection the ESP will create.
 After connecting to the ESP network with your other device, open a browser and got to 192.168.4.1
*/
 
#include <ESP8266WiFi.h>

wiWiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP Wifi Network", "password");

  Serial.print("Connecting");

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  //Serial.println("Client connected!");

  String req = client.readStringUntil('\r');
  Serial.println(req);

  client.flush();


  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "Hello from the ESP8266!";
  s += "</html>\n";

  client.print(s);
  delay(1);
  //Serial.println("Client disconnected");
}
