#include "AFMotor.h"
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);


char init_angle = 0;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

float angle;

int balance_angle_low = -130;
int balance_angle_high = -133;

#define offset 2

void goForward(){
  //Serial.println("forward");
  //return;
  motor1.run(FORWARD);      
  motor2.run(BACKWARD); 
  
}

void goBackward(){
 // Serial.println("Backward");
 // return;

  motor1.run(BACKWARD);      
  motor2.run(FORWARD); 
  
}


void setup() {

  Serial.begin(9600);           
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  pinMode(LED_BUILTIN, OUTPUT); 

  motor1.setSpeed(255);
  motor2.setSpeed(255);
}

void loop() {
  mpu6050.update();
  angle = mpu6050.getAngleY();

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  if(angle-offset >  balance_angle_low){
    goBackward();
    
    //goForward();
  }else if(angle+offset <  balance_angle_high){
     //goBackward();
    goForward();
   
  }
  
  //motor1.run(FORWARD);      
  //motor2.run(BACKWARD);  
}
