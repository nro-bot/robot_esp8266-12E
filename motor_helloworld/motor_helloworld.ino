/*
  Motor Hello World 
  Drives motors both in clockwise direction, then in ccw, so that robot drives in circles

  modified Oct 2016
  by Nancy Ouyang
 */

#define motor_dir_left D3

#define left_cw LOW 
#define left_ccw HIGH 

#define motor_pwm_left D1

int i = 0;

int speed_left = 800;
int speed_right = 1000;

void setup() {
  pinMode(motor_dir_left, OUTPUT);
  pinMode(motor_pwm_left, OUTPUT);
  Serial.begin(115200);
  Serial.println("");
}

void loop() {
  for ( i = 0; i < 1023; i++ ){
    digitalWrite(motor_dir_left, left_cw);
    analogWrite(motor_pwm_left, i);  
    Serial.println(i);
    delay(10);
  }
}
