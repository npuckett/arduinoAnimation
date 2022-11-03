/*
animationTools - by Nick Puckett https://github.com/npuckett/arduinoAnimation

Move between 2 angles for a specific duration of time;
rotationValues.startVal = 0;  //the angle to start at
rotationValues.endVal = 90;   //the angle to go to
rotationValues.travelTime = 7000; //how long to take to get there in milliseconds


*/


#include <Servo.h>
#include <animationTools.h>

Servo servo1;
int servoPin1 = 3;
int servoAngle;


Timeline rotationValues;  //define a new Timeline object called rotationValues


//inside setup define the parameters of the Timeline
void setup()
{

Serial.begin(9600);  

rotationValues.startVal = 0;  //the angle to start at
rotationValues.endVal = 90;   //the angle to go to
rotationValues.travelTime = 7000; //how long to take to get there in milliseconds

servo1.attach(servoPin1);
//set the servo to the startValue
servo1.write(rotationValues.startVal);

//give it time to get there
delay(2000);


}

void loop()
{

servoAngle = moveTo(rotationValues);
servo1.write(servoAngle);

} 