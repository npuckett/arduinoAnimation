
//simple object for holding XY coordinates
struct point 
{
float x;
float y;
};

//simple object for holding XY coordinates
struct valRange 
{
float minVal;
float maxVal;
};


//used for defining a triangle as inscribed in a circle. described as the angle from the center of the circle to define the point
struct tri_angles
{
int leg1;
int leg2;
int leg3;
};

//used to hold all of the data when calculating the rotation of a triangle
struct trianglePoints
{
int leg1X;
int leg1Y;
int leg2X;
int leg2Y;
int leg3X;
int leg3Y;
};


//helper object to create/hold keyframe data
struct Timeline
{
int totalKeys = 10;  
int timeKey[10];
int valKey[10];
int seqNumber = 1;
boolean timelineLoop = true;
int startupDelay = 0;
int currentValue;
unsigned long sequenceStart;
};

//this function retrieves the current value from a timeline object
int getTimelineValue(Timeline &inputTimeline)
{
  if((millis()-inputTimeline.startupDelay)-inputTimeline.sequenceStart>=(inputTimeline.timeKey[inputTimeline.seqNumber]-inputTimeline.timeKey[inputTimeline.seqNumber-1]))
  {
      if((inputTimeline.seqNumber+1)<inputTimeline.totalKeys)
      {
        inputTimeline.seqNumber++;
      }
  
      else
      { 
      	if(inputTimeline.timelineLoop)
      	{
        inputTimeline.seqNumber=1;
        }
        else
        {
       	inputTimeline.seqNumber=inputTimeline.totalKeys-1; 	
        }
      }
  
    inputTimeline.sequenceStart = (millis()-inputTimeline.startupDelay);
  }

inputTimeline.currentValue = map((millis()-inputTimeline.startupDelay),inputTimeline.sequenceStart,inputTimeline.sequenceStart+(inputTimeline.timeKey[inputTimeline.seqNumber]-inputTimeline.timeKey[inputTimeline.seqNumber-1]),inputTimeline.valKey[inputTimeline.seqNumber-1],inputTimeline.valKey[inputTimeline.seqNumber]);

return inputTimeline.currentValue;

  
}


//simple oscillation function
 //use millis() to step across a sin wave as an oscillator
 //map function converts to specified output range
uint8_t oscillate(int minVal, int maxVal, int offset, float multiplier, long tick)
{                                 
 uint8_t oscillValue = map((sin(float((tick+offset)*multiplier) * PI / 180.0)*1000),-1000,1000,minVal,maxVal+1);
 return oscillValue;
  
}



//rotation function broken into the single X coordinate
float rotatePointX(float centerX, int legAngle, float radius, float speedFactor, float rotationInput, int rotOffset)
{
float x =  centerX +(radius * cos(float(((rotationInput*speedFactor)+(legAngle+rotOffset))* PI / 180.0)));  
return x;
}  
//rotation function broken into the single X coordinate
float rotatePointY(float centerY, int legAngle, float radius, float speedFactor, float rotationInput, int rotOffset)
{
float y =  centerY +(radius * sin(float(((rotationInput*speedFactor)+(legAngle+rotOffset))* PI / 180.0)));    
return y;
}

//rotation function that returns a 'point' struct.  it just combines the previous 2 functions into 1
struct point rotatePoint(float centerX, float centerY, float radius, float speedFactor, float rotationInput, int rotOffset)
{
float x =  centerX +(radius * cos(float(((rotationInput*speedFactor)+rotOffset)* PI / 180.0))); 
float y =  centerY +(radius * sin(float(((rotationInput*speedFactor)+rotOffset)* PI / 180.0)));
point rotPoint = {x,y};
return rotPoint;	
}

struct trianglePoints rotateTriangle(float centerX, float centerY, int legAngle1, int legAngle2, int legAngle3, float radius, float speedFactor, float rotationInput, int rotOffset)
{
int x1 =  centerX +(radius * cos(float(((rotationInput*speedFactor)+(legAngle1+rotOffset))* PI / 180.0))); 
int y1 =  centerY +(radius * sin(float(((rotationInput*speedFactor)+(legAngle1+rotOffset))* PI / 180.0)));
int x2 =  centerX +(radius * cos(float(((rotationInput*speedFactor)+(legAngle2+rotOffset))* PI / 180.0))); 
int y2 =  centerY +(radius * sin(float(((rotationInput*speedFactor)+(legAngle2+rotOffset))* PI / 180.0)));
int x3 =  centerX +(radius * cos(float(((rotationInput*speedFactor)+(legAngle3+rotOffset))* PI / 180.0))); 
int y3 =  centerY +(radius * sin(float(((rotationInput*speedFactor)+(legAngle3+rotOffset))* PI / 180.0)));

trianglePoints rotTriangle = {x1,y1,x2,y2,x3,y3};
return rotTriangle;

}




