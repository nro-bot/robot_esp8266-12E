#include <SoftwareSerial.h>

#define SERIAL_RX     D5  // pin for SoftwareSerial RX
#define SERIAL_TX     D6  // pin for SoftwareSerial TX

#define LED_PIN D0

SoftwareSerial mySerial(SERIAL_RX, SERIAL_TX); // (RX, TX. inverted, buffer)

void setup() {
  mySerial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  pinMode(SERIAL_RX, INPUT);
  pinMode(SERIAL_TX, OUTPUT);
  Serial.begin(115200);
  Serial.println("hello!");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  
  
  while (Serial.available() > 0) {
    int command = Serial.parseInt();
    
    if (Serial.read() == '\n') {
      Serial.println(command);
              digitalWrite(LED_PIN, LOW);

      mySerial.write(command);
        digitalWrite(LED_PIN, HIGH);
       
    }
  }
}
