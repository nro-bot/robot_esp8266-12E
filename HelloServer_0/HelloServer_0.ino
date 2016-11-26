/* 
 Source: https://www.gitbook.com/book/krzychb/esp8266wifi-library/details
 In the serial monitor, you should see
   Connecting...............
   Connected, IP address: 192.168.1.10
*/
 
#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("ssid", "password");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {}
