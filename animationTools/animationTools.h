
//simple object for holding rangeValues
struct valRange 
{
float minVal;
float maxVal;
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








