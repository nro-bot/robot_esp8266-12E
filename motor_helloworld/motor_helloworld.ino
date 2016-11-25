/*
  Motor Hello World 

  Drives motors in same direction.
  Motors should accelerate, switch directions, and repeat
  
  Note that one of the motor pins overlaps with LED pin D4, so when the left wheel is going CW, the LED light close the ESP chip will turn on
  Note that we opted to swap the motor wires on the right motor so that LOW is backwards for both motors
  
  We define arbitrarily Left CW = backwards
  
  
  Hardware: 
  * NodeMCU Amica DevKit Board (ESP8266 chip)
  * Motorshield for NodeMCU 
  * 2 motors + 2 wheels + motor chassis with caster
  * Left motor connected to D3 (BLK/A- and RED/A+ on the shield)
  * Right motor connected to D4, with wires swapped (RED/B- and BLK/B+ on the shield)

  modified Nov 2016
  by Nancy Ouyang
*/

#define led_pin D0

#define motor_dir_left D3
#define motor_dir_right D4

#define dir_back LOW
#define dir_fwd HIGH 

#define motor_pwm_left D1
#define motor_pwm_right D2

int i = 0;

int speed_left = 800;
int speed_right = 1000;

void setup() {
  pinMode(motor_dir_left, OUTPUT);
  pinMode(motor_pwm_left, OUTPUT);
  pinMode(motor_dir_right, OUTPUT);
  pinMode(motor_pwm_right, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("BEGIN");
}

void loop() {
  Serial.println("~~~~~~~~~~~~~~Backwards~~~~~~~~~~~~~~~~~~");
  delay(10);

  for ( i = 800; i < 1023; i++ ){
    digitalWrite(motor_dir_left, dir_back);
    analogWrite(motor_pwm_left, i);  
    digitalWrite(motor_dir_right, dir_back);
    analogWrite(motor_pwm_right, i);  
  
    Serial.println(i);
    
    delay(10);
  }
 
 Serial.println("================Forwards================");
 delay(10);

 for ( i = 800; i < 1023; i++ ){
    digitalWrite(motor_dir_left, dir_fwd);
    analogWrite(motor_pwm_left, i);  
    digitalWrite(motor_dir_right, dir_fwd);
    analogWrite(motor_pwm_right, i);  
    
    Serial.println(i);
    
    delay(10);
  } 
}
