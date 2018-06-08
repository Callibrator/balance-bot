#include "AFMotor.h"
#include <MPU6050_tockn.h>
#include <Wire.h>

//initializing communication with mpu5060
MPU6050 mpu6050(Wire);

//initializing communication with dc motors
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

//current angle of the robot
float angle;


//maximum and minimum Y angle that the robot must have in order to stay balanced to its center of mass
int balance_angle_low = -130;
int balance_angle_high = -133;

//Offset Fix for your current angle.
#define offset 2

//Robot moving forward function
void goForward(){

  motor1.run(FORWARD);      
  motor2.run(BACKWARD); 
  
}
//robot moving backward function
void goBackward(){

  motor1.run(BACKWARD);      
  motor2.run(FORWARD); 
  
}


void setup() {
  //Serial communication initialization
  Serial.begin(9600);          
  //Gyroscope requires wire communication.
  Wire.begin();
  
  //Prepare gyroscope & initialize gyrocope offsets plus find your current angle
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  
  //LED_BUILTIN mode = OUTPUT. It may be used to send signals to the user of the robot in case somthing is wrong.
  //At this point I am not using it at all
  pinMode(LED_BUILTIN, OUTPUT); 

  
  //Motor Speed.
  motor1.setSpeed(255);
  motor2.setSpeed(255);
}

void loop() {
  //Update the angles of the gyroscope
  mpu6050.update();
  
  //Get the Last Saved Y angle of your gyroscope. mpu6050.update is required before this command.
  angle = mpu6050.getAngleY();

  //We assume that the robot is balanced and we stop the motors from rotating.
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  
  //Checking if the current robot angle fixed by offset is below minimum angle and if this is true we move backard in order to
  //balance the robot. Keep in mind that we stop the motors before this statement but because of the  time being so small we
  //do not have any problem doing this.
  //Although it may be better to put another if statement because this slows down the mainloop and the gyroscope may have some
  //accuracy problems when the rotation is very fast.
  if(angle-offset >  balance_angle_low){
    goBackward(); 
   //We do the same thing for the maximum angle but we move forward instead... 
  }else if(angle+offset <  balance_angle_high){
    goForward();
   
  }
  

}
