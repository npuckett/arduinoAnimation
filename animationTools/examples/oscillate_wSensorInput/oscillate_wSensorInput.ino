/*
animationTools - by Nick Puckett https://github.com/npuckett/arduinoAnimation
Oscillate with sensor Trigger
when the sensor value goes below the treshold it moves at idle speed
when above the threshold it moves at the max speed.

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
int servoSpeedMax1 = 200;  ///0 slowest - 1000 max speed
int servoSpeedIdle1 = 50;  ///0 slowest - 1000 max speed
int servoSpeed1;

int sensorPin = A6;
int sensorVal;
int sensorthreshold = 500;


void setup()
{
Serial.begin(9600);
servo1.attach(servoPin1);



}

void loop() 
{
//read sensor
sensorVal = analogRead(sensorPin);

if(sensorVal<=sensorthreshold)
{
  servoSpeed1 = servoSpeedIdle1;//set to the idling speed
}
else
{
  servoSpeed1 = servoSpeedMax1;//set to the max speed
}




servoAngle1 = oscillate(servoMinAngle1,servoMaxAngle1,0,servoSpeed1);
servo1.write(servoAngle1);

Serial.println(sensorVal);



}




