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


Timeline rotationValues1;  //define a new Timeline object called rotationValues
Timeline rotationValues2;


int sensorPin = A6;
int sensorVal;
int triggerVal = 500;


void setup() 
{
  Serial.begin(9600);

  rotationValues1.timeKey[0]=0;  //@ time 0 milliseconds
  rotationValues1.valKey[0]=0;  //rotation 0 degrees

  rotationValues1.timeKey[1]=4000;  //@ time 4 seconds
  rotationValues1.valKey[1]=50;    //rotation 50 degree

  rotationValues1.timeKey[2]=5000;  //@ time 5 seconds
  rotationValues1.valKey[2]=50;    //rotation 50 degrees (ie hold it there for 1 second)

  rotationValues1.timeKey[3]=6000; //@ time 6 seconds
  rotationValues1.valKey[3]=0;     //rotation 0 degrees

  //you must define how many keyframes you have created
  rotationValues1.totalKeys = 4;

  //by default the timelines loop, but you can turn that off with
  //rotationValues1.loop = false;
////////////////second timeline
rotationValues2.timeKey[0]=0;   //@time 0 
rotationValues2.valKey[0]=0;    //rotation 0 degrees

rotationValues2.timeKey[1]=400; //@ time 0.4 seconds
rotationValues2.valKey[1]=70;   //rotation 70 degrees

rotationValues2.timeKey[2]=2000; //@ time 2 seconds
rotationValues2.valKey[2]=0;    //rotation 0 degrees

rotationValues2.totalKeys = 3;
  //by default the timelines loop, but you can turn that off with
  //rotationValues2.loop = false;


servo1.attach(servoPin1);

//set the servo to the startValue
servo1.write(rotationValues1.valKey[0]);

delay(2000);
  

}

void loop() 
{
//read from the sensor
sensorVal = analogRead(sensorPin);


if(sensorVal<=triggerVal)
{
  //get the current value from the timeline
  servoAngle = getTimelineValue(rotationValues1);

  //reset the other timeline
  resetTimeline(rotationValues2);
} 
  else
  {
      //get the current value from the timeline
  servoAngle = getTimelineValue(rotationValues2);

  //reset the other timeline
  resetTimeline(rotationValues1);
  }
  
  
  
  //write the value to the servo
  servo1.write(servoAngle);


Serial.println(servoAngle);

}
