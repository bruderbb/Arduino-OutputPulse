/*
This program describes the basic usage of the OutputPulse library
*/

#include <Arduino.h>
#include <OutputPulse.h>
uint32_t now            = 0;    // variable for storing the current time
uint32_t outputInterval = 1000; // the output pulse is triggered in this interval
uint32_t lastPulseTime  = 0;    // Variable for storing the last pulse time


char outputPin = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino-OutputPulse demonstration");
  // setting up the output pin we want to pulse
  pinMode(A0, OUTPUT);
  OutputPulse pulse (otputPin, 250, true);
  pulse.begin();
}

void loop() {
  now = millis();
  pulse.update();
  // if interval since last Pulse has passed reset time and trigger output
  if ((lastPulseTime + outputInterval) >= now)
  {
    lastPulseTime = now;
    pulse.trigger();
  }

}
