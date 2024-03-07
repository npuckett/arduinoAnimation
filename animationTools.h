#include "Arduino.h"

// Toggle class definition
class Toggle {
  private:
    unsigned long lastSwitch;
    bool currentState;
    
  public:
    Toggle(); // Constructor declaration

    // Method to update and get the current state
    // Takes toggleRate as an argument
    bool update(int toggleRate);
};

// Toggle class constructor implementation
Toggle::Toggle() {
  lastSwitch = 0; // Initialize lastSwitch to 0
  currentState = false; // Initialize currentState to false
}

// Method to update and get the current state based on the toggleRate
bool Toggle::update(int toggleRate) {
  // Check if the specified rate time has passed
  if(millis() - lastSwitch >= toggleRate) {
    lastSwitch = millis(); // Update the last switch time to current time
    currentState = !currentState; // Toggle the state
  }
  return currentState; // Return the current state
}



//helper object to create/hold keyframe data
struct Timeline
{
int totalKeys = 0;  
int timeKey[20];
int valKey[20];
int seqNumber = 1;
boolean loop = true;
int startupDelay = 0;
int currentValue =0;
unsigned long sequenceStart;
int currentTime;

int startVal;
int endVal;
int travelTime;
boolean isPlaying = false;
boolean arrived = false; 

// Method to add a keyframe
    void addKey(int time, int val) {
        if (totalKeys < 20) { // Check not to exceed array size
            timeKey[totalKeys] = time;
            valKey[totalKeys] = val;
            totalKeys++; // Increment totalKeys since we added a key
        } else {
            // Optionally handle the error if too many keys are added
        }
    }

};
int moveTo(Timeline &inputTimeline)
{
    if(!inputTimeline.isPlaying)
    {
     inputTimeline.sequenceStart = millis();
     inputTimeline.isPlaying = true;  
    }


   inputTimeline.currentTime = millis()-inputTimeline.sequenceStart; 
   int outVal = inputTimeline.currentValue;
    if(inputTimeline.currentTime<=inputTimeline.travelTime)
    {
     inputTimeline.currentValue= map(inputTimeline.currentTime,0,inputTimeline.travelTime,inputTimeline.startVal,inputTimeline.endVal);
     outVal = inputTimeline.currentValue;
    }
    else
    {
    inputTimeline.arrived = true;
    }

return outVal;
}
int resetMove(Timeline &inputTimeline)
{
    inputTimeline.isPlaying=false;
    inputTimeline.arrived = false;
    return inputTimeline.startVal;

}
int resetTimeline(Timeline &inputTimeline)
{
    inputTimeline.isPlaying=false;
    inputTimeline.arrived = false;
    inputTimeline.seqNumber = 1;
    return inputTimeline.valKey[0];

}



//this function retrieves the current value from a timeline object
int getTimelineValue(Timeline &inputTimeline)
{
  //currentTime = millis()-inputTimeline.sequenceStart;
  if(!inputTimeline.isPlaying)
    {
     inputTimeline.sequenceStart = millis();
     inputTimeline.isPlaying = true;  
    }

    inputTimeline.currentTime = millis()-inputTimeline.sequenceStart;
    inputTimeline.travelTime = (inputTimeline.timeKey[inputTimeline.seqNumber]-inputTimeline.timeKey[inputTimeline.seqNumber-1]); 
    inputTimeline.startVal = inputTimeline.valKey[inputTimeline.seqNumber-1];
    inputTimeline.endVal = inputTimeline.valKey[inputTimeline.seqNumber];

  int outVal = inputTimeline.currentValue;  

  if(inputTimeline.currentTime<=inputTimeline.travelTime)
  {
    inputTimeline.currentValue= map(inputTimeline.currentTime,0,inputTimeline.travelTime,inputTimeline.startVal,inputTimeline.endVal);
    outVal = inputTimeline.currentValue;
  }
    else
    {
      if((inputTimeline.seqNumber+1)<inputTimeline.totalKeys)
      {
        inputTimeline.seqNumber++;
        inputTimeline.isPlaying = false;
      }
  
      else
      { 
      	if(inputTimeline.loop)
      	{
        inputTimeline.seqNumber=1;
        inputTimeline.isPlaying = false;
        }
        else
        {
       	inputTimeline.seqNumber=inputTimeline.totalKeys-1; 	
        }
      }



    }




  
    return outVal;
    
  }



  




//simple oscillation function
 //use millis() to step across a sin wave as an oscillator
 //map function converts to specified output range
int oscillate(int minVal, int maxVal, int offset, int speed)
{    
                            
 int oscillValue = map((sin(float((millis()+offset)*(float(speed)/1000)) * PI / 180.0)*1000),-1000,1000,minVal,maxVal+1);
 return oscillValue;
  
}








