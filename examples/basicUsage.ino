/*
This program describes the basic usage of the OutputPulse library

it triggers an output pulse of 500 ms Length every 5000 milliseconds
*/

#include <Arduino.h>
#include <OutputPulse.h>
uint32_t now            = 0;    // variable for storing the current time
uint32_t outputInterval = 5000; // the output pulse is triggered in this interval (ms)
uint32_t lastPulseTime  = 0;    // Variable for storing the last pulse time

// This sets the physical output pin we want to use
char outputPin = A0;

void setup() {
  // let's set up serial so we can see what happens
  Serial.begin(9600);
  Serial.println("Arduino-OutputPulse demonstration");
  // setting up the outputPin we want to pulse
  pinMode(outputPin, OUTPUT);

  // here we set up an OutputPulse object called "pulse"
  // 1st argument: the pin we want to usage
  // 2nd argument: the output pulse length in ms
  // 3rd argument: the output pulse polarity
  OutputPulse pulse (otputPin, 500, true);

  // start the pulse
  pulse.begin();
}

void loop() {
  // get the current time
  now = millis();
  // in every loop iteration (or at least as often as possible)
  // we have to call the xxxx.update() function for every OutputPulse-object
  // we created... in this case just for "pulse"
  pulse.update();
  // if interval since last pulse-trigger has passed
  // we reset time and start a new output pulse
  if ((lastPulseTime + outputInterval) >= now)
  {
    //give some feedback over serial interface
    Serial.println("A new pulse has just been triggered...")
    // reset the timer
    lastPulseTime = now;
    //this triggers the output pulse
    pulse.trigger();
  }

}
