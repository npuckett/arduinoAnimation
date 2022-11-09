# Animation Tools

The animation tools library is a small set of helper functions and data structures for Arduino that use basic tools and methods of time-based animation to control various actuators.  The tools have been used to control LEDs, stepper motors, servos, and piezo buzzers.  The core of the library is based around 2 basic functions – oscillation & timeline– that can be layered onto eachother for more complex behaviours.These functions are all based on timers, so they do not block any other input/output functions used in a sketch.

```arduino
To use this library: 
-Install it by downloading the folder and copying the folder to your Arduino Libray folder in Documents. 
-Include it in your sketch using
#include <animationTools.h>
```

## Functions

### Oscillate
#### Returns: integer
This function uses a simple sin wave to drive a continuous fade between 2 values and returns an integer.

The function has 5 inputs that can be changed dynamically
```arduino
oscillate(int minVal, int maxVal, int offset, int speed)

minVal //starting value of the oscillation
maxVal //end value of the oscillation
offset //moves initial start of the oscillation sequence. 
speed //used to change the speed of the oscillation (integer between 0 - 1000, smaller number = slower)
timeInput//value used to step across the sin wave (typically millis())
```

#### Examples:

```arduino 
//oscillate between 0 <-> 255 with a multiplier speed of 100
int ledBrightness = oscillate(0,255,0,100);

//oscillate between 20 <–> 150 with a multiplier speed of 500 
int servoRotation = oscillate(20,150,0,500); 
```


Note: oscillate is designed to function as a very simple interpolation mechanism. If you require more precise or complex controls over values, use Timeline.

### getTimelineValue
#### Returns: integer
This method allows you to create a flexible keyframe animation controlled by Arduino

#### Examples

```arduino
Timeline rotationValues:  //define a new Timeline object called rotationValues


//inside setup define the keyframe values at points on the Timeline
void setup()
{
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

//allow 2 seconds for the servo to reset
delay(2000);

}

void loop()
{
//to return the current value pass the object in the getTimelineValue function
int currentRotation = getTimelineValue(rotationValues); 
servo1.write(currentRotation);
} 
```

```arduino
Timeline brightnessValues:  //define a new Timeline object called brightnessValues


//inside setup define the keyframe values at points on the Timeline
void setup()
{
brightnessValues.timeKey[0] = 0;   //set a brightness value of 0 at time 0
brightnessValues.valKey[0] = 0;

brightnessValues.timeKey[1] = 500;   //hold that value at 0 for 500 milliseconds
brightnessValues.valKey[1] = 0;

brightnessValues.timeKey[2] = 1500;   //fade from 0 to 255 over 1 second
brightnessValues.valKey[2] = 255;

brightnessValues.timeKey[3] = 2000;   //hold that value for 500 milliseconds
brightnessValues.valKey[3] = 255;

brightnessValues.timeKey[4] = 4000;   //fade back to 0 over 2 seconds
brightnessValues.valKey[4] = 0;

brightnessValues.totalKeys = 5;   //manually tell it how many keyframes

}

void loop()
{
//to return the current value pass the object in the getTimelineValue function
int currrentBrightness = getTimelineValue(brightnessValues); 
analogWrite(6,currentBrightness);

} 
```
### resetTimeline
#### Returns: nothing
When triggering a Timeline behaviour dynamically or switching between 2 or more, you can use resetTimeline to move its playhead by to the beginning

#### Examples
```arduino
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
```  
### moveTo
#### Returns: integer  
This is a simplified version of a Timeline with only 2 values

#### Examples
```arduino
Timeline rotationValues;  //define a new Timeline object called rotationValues

//inside setup define the parameters of the Timeline
void setup()
{

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
```
### resetMove
#### Returns: Nothing  
When triggering a Timeline behaviour dynamically or switching between 2 or more, you can use resetTimeline to move its playhead by to the beginning

#### Examples
```arduino
void loop()
{
//read from the sensor
sensorVal = analogRead(sensorPin);

if(sensorVal<=triggerVal)
{
servoAngle = moveTo(rotationValues);
}
else
{
servoAngle = resetMove(rotationValues);
}
}
```



### Data Structures


### valRange
Similar to *point* this data structure is useful when organizing oscillation functions. It has 2 parameters: minVal maxVal

```arduino
valRange moveXRange;
moveRange.minVal = 10;
moveRange.maxVal = 100;
```


### Timeline
This function creates a method for using keyframe values in time as a means of controlling outputs in Arduino.  It consists of two parts: the Timeline structure and the getTimelineValue function.  The timeline of keyframe values can be set at the beginning of the sketch or changed dynamically at runtime. The function uses only linear interpolation between the values/time. Note: This is still an early version of the code. It has some quirks.

All timelines have the following parameters. Where X is the index of the array
```
.timeKey[X]  
.valKey{X]
```
These 2 parameters are typically defined together in the same manner you would input this type of data into an animation interface.  Define a value at a time.   The index should start at 0 and must be the same for the timeKey and valKey.  



```
.totalKeys
```
At this point, you must manually define the total number of keyframes that you have created.  The maximum number of values is 10, but can be changed. (This will be fixed in a future version of the library)  


```
.timelineLoop
```
This is True by default, but if you want the timeline to stop when it reaches the end it can be set to False.  


```
.startVal
```
When using moveTo, you can set this parameter as the starting value on the timeline to animate FROM  


```
.endVal
```
When using moveTo, you can set this parameter as the starting value on the timeline to animate TO  


```
.travelTime
```
When using moveTo, this defines the amount of time in milliseconds to move between the .startVal and .endVal  


To use the function you must create an instance of a Timeline object, define it’s parameters.

#### Example:

```arduino
Timeline rotationValues:  //define a new Timeline object called rotationValues


//inside setup define the parameters of the Timeline
void setup()
{
rotationValues.timeKey[0] = 0;   //set a rotation of 10 at time 0
rotationValue.valKey[0] = 10;

rotationValues.timeKey[1] = 100;   //set a rotation of 100 at 1 second
rotationValue.valKey[1] = 1000;

rotationValues.timeKey[2] = 100;   //stay at 100 for 1 more second
rotationValue.valKey[2] = 2000;

rotationValues.timeKey[3] = 50;   //move to 50 over 500 milliseconds
rotationValue.valKey[3] = 2500;

rotationValues.timeKey[4] = 170;   //set a rotation of 170
rotationValue.valKey[4] = 3500;

rotationValues.timeKey[5] = 0;   //set rotation back to 0
rotationValue.valKey[5] = 4000;

rotationValues.totalKeys = 6;   //manually tell it how many keyframes

}

void loop()
{
int currentRotation = getTimelineValue(rotationValues); //to return the current value pass the object in the getTimelineValue function

} 
```











