// Include Arduino header for the millis() function

#include "animationTools.h"
// Toggle class definition


// Example of how to use the Toggle class
// Global Toggle object
Toggle buzzRate;
int buzzerPin = 5;
void setup() {
  // Your setup code here
  pinMode(buzzerPin,OUTPUT);
}

void loop() {
  // Example usage of the Toggle class
  bool buzzState = buzzRate.update(200);
  // Use ledState to control an LED or any other binary output
  digitalWrite(buzzerPin,buzzState);
}
