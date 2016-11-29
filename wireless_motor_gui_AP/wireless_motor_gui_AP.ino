/*
  attempt AP control of robot
*/

#include <Arduino.h>

#include <ESP8266WiFi.h>

#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>

#include <ESP8266mDNS.h>
#include <FS.h>

const int LED_PIN = D0;

const int MOTOR_PWM_LEFT = D1;
const int MOTOR_PWM_RIGHT = D2;

const int MOTOR_DIR_LEFT = D3;
const int MOTOR_DIR_RIGHT = D4;

#define MOTOR_BACK LOW
#define MOTOR_FWD HIGH


// WiFi parameters
const char* ssid = "ESP Whee";
const char* password = "my_password";

ESP8266WebServer server = ESP8266WebServer(80);
WebSocketsServer webSocket = WebSocketsServer(81);

String html_home;

//String css_code;
//String css_bootstrap;
//String js_code;
//String js_aREST;
//String js_ajaxq;
//String js_jquery;


void setup() {
    WiFi.softAP(ssid, password);

    Serial.begin(115200);

    Serial.println();

    setupServer();

    setupPins();
}

void loop() {
    webSocket.loop();
    server.handleClient();
}



//
// Movement Functions //
//

int stop() {
  //analogWrite(MOTOR_PWM_LEFT, 0);
  //analogWrite(MOTOR_PWM_RIGHT, 0);
  digitalWrite(LED_PIN, HIGH);
  Serial.println("stop");
}

int forward() {
  digitalWrite(LED_PIN, LOW);
  Serial.println("forward");
  //digitalWrite(MOTOR_DIR_LEFT, MOTOR_FWD);
  //digitalWrite(MOTOR_DIR_RIGHT, MOTOR_FWD);

  //analogWrite(MOTOR_PWM_LEFT, 800);
  //analogWrite(MOTOR_PWM_RIGHT, 800);
}


//
// Setup Methods //
//
void prepareFile() {
  
    Serial.println("Prepare file system");
    SPIFFS.begin();
  
    File file = SPIFFS.open("/controls.html", "r");
    if (!file) {
        Serial.println("HTML file open failed");  
    } 
    else {
        Serial.println("HTML file open success");

        html_home = "";
        while (file.available()) {
            //Serial.write(file.read());
            String line = file.readStringUntil('\n');
            html_home += line + "\n";
        }
        file.close();

        //Serial.print(html_home);
    }

}

//
// Setup //
//

void setupPins() {
    // setup LEDs and Motors
    Serial.println("Setup LED pins");
    pinMode(LED_PIN, OUTPUT);    //Pin D0 is LED
    digitalWrite(LED_PIN, LOW); //Initial state is ON (LOW)

    pinMode(MOTOR_PWM_LEFT, OUTPUT);
    pinMode(MOTOR_DIR_LEFT, OUTPUT);
    pinMode(MOTOR_PWM_RIGHT, OUTPUT);
    pinMode(MOTOR_DIR_RIGHT, OUTPUT);

    // Set initial speed to 0
    analogWrite(MOTOR_PWM_LEFT, 0);
    analogWrite(MOTOR_PWM_RIGHT, 0);
}

void setupServer() {
    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    // read the html code to html_homes
    prepareFile();


    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    // start webSocket server
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);

    if(MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
    }

    // handle index
    server.on("/", []() {
        // send home.html
        server.send(200, "text/html", html_home);
    });

    server.begin();

    // Add service to MDNS
    MDNS.addService("http", "tcp", 80);
    MDNS.addService("ws", "tcp", 81);

    Serial.printf("Server Start\n");
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {

    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED: 
        {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

            // send message to client
            webSocket.sendTXT(num, "Connected");
            break;
        }
        case WStype_TEXT:
            Serial.printf("[%u] get text: %s\n", num, payload);

            if (payload[0] == '#') {
                if(payload[1] == 'F') {
                  forward();
                }
                else {
                  stop();
                }
            }

            break;
    }
}
