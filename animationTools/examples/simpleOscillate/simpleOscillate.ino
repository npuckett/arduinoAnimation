/*
animationTools - by Nick Puckett https://github.com/npuckett/arduinoAnimation
simple oscillate

Connect a standard servo to digital pin 3
adjust the min / max angle to set what the servo moves between
speed is between 0 - 1000 



*/


#include <Servo.h>
#include <animationTools.h>

Servo servo1;
int servoPin1 = 3;
int servoAngle1;
int servoMinAngle1 = 0;
int servoMaxAngle1 = 90;
int servoSpeed1 = 200;  ///0 slowest - 1000 max speed


void setup()
{
Serial.begin(9600);
servo1.attach(servoPin1);



}

void loop() 
{

servoAngle1 = oscillate(servoMinAngle1,servoMaxAngle1,0,servoSpeed1);
servo1.write(servoAngle1);

Serial.println(servoAngle1);



}




