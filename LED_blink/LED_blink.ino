/*  
  LED Blink (now with Analog Read)
  
  Turns on the two LEDs on for one second, then off for one second, repeatedly.
  Reads from the analog input pin and prints out to serial at 115200 baud
  
  Note that HIGH is OFF and LOW is ON
  D0 is closer to the USB port
  D4 is further away from the USB port (right up against the ESP8266 chip)

  Hardware: NodeMCU Amica DevKit Board (ESP8266 chip)
  
  modified Nov 2016
  by Nancy Ouyang
*/


#define LED_PIN D0
#define LED_PIN_2 D4
#define ANALOG_PIN A0

int sensorValue = 999;
 
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(ANALOG_PIN, INPUT);

  digitalWrite(LED_PIN, HIGH);
  digitalWrite(LED_PIN_2, HIGH);
  
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(LED_PIN_2, LOW);
  sensorValue = analogRead(ANALOG_PIN);
  Serial.println(sensorValue);

  delay(300);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_PIN_2, HIGH);
  sensorValue = analogRead(ANALOG_PIN);
  Serial.println(sensorValue);

  delay(300);
}
