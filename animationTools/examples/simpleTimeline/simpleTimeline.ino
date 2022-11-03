/*
animationTools - by Nick Puckett https://github.com/npuckett/arduinoAnimation

create a keyframe style animation for the servo

Timeline rotationValues;

  rotationValues.timeKey[0]=0;  //@ time 0 milliseconds
  rotationValues.valKey[0]=0;  //rotation 0 degrees

  rotationValues.timeKey[1]=4000;  //@ time 4 seconds
  rotationValues.valKey[1]=50;    //rotation 50 degree

  rotationValues.timeKey[2]=5000;  //@ time 5 seconds
  rotationValues.valKey[2]=50;    //rotation 50 degrees (ie hold it there for 1 second)

  rotationValues.timeKey[3]=6000; //@ time 6 seconds
  rotationValues.valKey[3]=0;     //rotation 0 degrees

  //you must define how many keyframes you have created
  rotationValues.totalKeys = 4;





*/


#include <Servo.h>
#include <animationTools.h>


Servo servo1;
int servoPin1 = 3;
int servoAngle;


Timeline rotationValues;  //define a new Timeline object called rotationValues


void setup() 
{
  Serial.begin(9600);

  rotationValues.timeKey[0]=0;  //@ time 0 milliseconds
  rotationValues.valKey[0]=0;  //rotation 0 degrees

  rotationValues.timeKey[1]=4000;  //@ time 4 seconds
  rotationValues.valKey[1]=50;    //rotation 50 degree

  rotationValues.timeKey[2]=5000;  //@ time 5 seconds
  rotationValues.valKey[2]=50;    //rotation 50 degrees (ie hold it there for 1 second)

  rotationValues.timeKey[3]=6000; //@ time 6 seconds
  rotationValues.valKey[3]=0;     //rotation 0 degrees

  //you must define how many keyframes you have created
  rotationValues.totalKeys = 4;

  //by default the timelines loop, but you can turn that off with
  //rotationValues.loop = false;


  servo1.attach(servoPin1);
//set the servo to the startValue
servo1.write(rotationValues.valKey[0]);

delay(2000);
  

}

void loop() 
{
  //get the current value from the timeline
  servoAngle = getTimelineValue(rotationValues);
  
  servo1.write(servoAngle);


Serial.println(servoAngle);

}
