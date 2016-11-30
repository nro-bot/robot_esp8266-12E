# robot_esp8266-12E

[!Profile of robot](robot.jpg)

[!Side profile of robot](robot_sideprofile.jpg)

[!HTML GUI screenshot](screenshot.jpg)

Current working demo in wireless_motor_gui_AP

ESP8266 wirelessly controlled robot car 

1. NodeMCU Amica board + 

2. ESP8266 SMT Module - ESP-12E, however you don't want to work directly with the SMT, but instead with the:
NodeMCU = open-source firmware, may also refer to their very popular devkit board design which is available from $8 to $10

* https://github.com/nodemcu/nodemcu-devkit-v1.0

3. Motor Shield Board (L293DD) for NodeMCU: available for $5

* https://smartarduino.gitbooks.io/user-mannual-for-esp-12e-motor-shield/content/index.html
* http://www.smartarduino.com/nodemcu-motor-l293d-shield-board-for-esp-12e_p94570.html

4. Four motors, caster, and metal chassis from aliexpress


## Misc. Documentation
Arduino Support

* http://www.instructables.com/id/Programming-ESP8266-ESP-12E-NodeMCU-Using-Arduino-/?ALLSTEPS

NodeMCU ESP-12E Pin mapping
In Arduino, add support for NodeMCU board. (a lot of annoying GUI stuff)
Then can program directly in Arduino over USB cable :)

* https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/example-sketch-ap-web-server

"This example demonstrates how to turn the ESP8266 into an access point (AP), and serve up web pages to any connected client."

* https://github.com/tzapu/WiFiManager

## Troubleshooting

* Does LED_blink work?

Both LEDs should blink, but alternating. Serial monitor should display low (<10) values.

* Does motor_helloworld work?

Both motors should move, specifically they should accelerate, switch directions, and repeat. Serial monitor should display commanded speed.

