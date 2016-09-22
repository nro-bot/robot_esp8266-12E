/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#define motor_dir_left D3
#define motor_dir_right D4

#define right_cw HIGH 
#define right_ccw LOW
#define left_cw LOW 
#define left_ccw HIGH 

#define motor_pwm_left D1
#define motor_pwm_right D2

int speed_left = 1000;
int speed_right = 1000;

void setup() {
  pinMode(motor_dir_left, OUTPUT);
  pinMode(motor_dir_right, OUTPUT);
  pinMode(motor_pwm_left, OUTPUT);
  pinMode(motor_pwm_right, OUTPUT);
}

void loop() {
  digitalWrite(motor_dir_left, left_cw);
  digitalWrite(motor_dir_right, right_cw);


  analogWrite(motor_pwm_left, speed_left);  
  analogWrite(motor_pwm_right, speed_right);
  delay(300);


  digitalWrite(motor_dir_left, left_ccw);
  digitalWrite(motor_dir_right, right_ccw);


  analogWrite(motor_pwm_left, speed_left);
  analogWrite(motor_pwm_right, speed_right);  
  delay(1000);
}
