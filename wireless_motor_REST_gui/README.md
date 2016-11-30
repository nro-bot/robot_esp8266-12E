# esp8266-robot
https://openhomeautomation.net/build-wifi-controlled-robot-esp8266/

Install aREST (Arduino REST) library via Sketch > Manage Libraries > Add > aREST
Upload code after modifying it to have the ssid and password for your wifi Interent connection
In browser, open the ./interfaces/demo.html file. It has four buttons. Press them to move the motors.


   Hardware: 
    * NodeMCU Amica DevKit Board (ESP8266 chip)
    * Motorshield for NodeMCU 
    * 2 motors + 2 wheels + motor chassis with caster
    * Left motor connected to D3 (BLK/A- and RED/A+ on the shield)
    * Right motor connected to D4, with wires swapped (RED/B- and BLK/B+ on the shield)

Troubleshooting:
192.168.0.10 (or the IP address printed out to the serial monitor) should reveal
{"variables": { }, "id": "1", "name": "robot", "hardware": "esp8266", "connected": true}
