/*
Adds the ability to construct a pulse output which, when triggered, generates a
pulse of specific length on the specified output
*/

#include <PulseOutput.h>

// constructors
// constructor for just the pin
PulseOutput::PulseOutput (
  const char pin
)
{
  startTime_      = 0;
  pin_            = pin;
  pulseLength_    = 25;     // predefined pulseLength
  pulsePolarity_  = true;   // predefined pulsePolarity
} // end of PulseOutput::PulseOutput

// constructor for pin and pulseLength
PulseOutput::PulseOutput (
  const char pin,
  const unsigned long pulseLength
)
{
  startTime_      = 0;
  pin_            = pin;
  pulseLength_    = pulseLength;
  pulsePolarity_  = true;
} // end of PulseOutput::PulseOutput

// constructor for pin, pulseLength and pulsePolarity
PulseOutput::PulseOutput (
  const char pin,
  const unsigned long pulseLength,
  const bool pulsePolarity
)
{
  startTime_ = 0;
  pin_ = pin;
  pulseLength_ = pulseLength;
  pulsePolarity_ = pulsePolarity;
} // end of PulseOutput::PulseOutput

void PulseOutput::begin()
{
  // set the pin as output
  pinMode(pin_, OUTPUT);
  // set the initial output value based on pulsePolarity
  digitalWrite(pin_, !pulsePolarity_);
} // end of PulseOutput::begin


/*
@brief Triggers an output pulse
*/
void PulseOutput::trigger()
{
  // set the start time
  startTime_ = millis();
  // set the variable to indicate a pulse is currently active
  pulseActive_ = true;
  // activate the output
  digitalWrite(pin_, pulsePolarity_);
} // end of PulseOutput::trigger


void PulseOutput::update()
{
  // do nothing if no pulse is active
  if (!pulseActive_)
  {
    return;
  }

  // detect millis counter overflow (value is smaller than startTime_)
  if (millis () < startTime_)
  {
    // reset the startTime_ to current
    startTime_ = millis();
    return;
    // worst case scenario: the output pulse is double the pulseLength (minus 1)
  }

  // a variable for saving the current time
  unsigned long now = millis();
  // if the stop time has been reached turn the pulse OFF
  if (now >= (startTime_ + pulseLength_))
  {
    // reset the output pin
    digitalWrite(pin_, !pulsePolarity_);
    // reset the active status
    pulseActive_ = false;
  }
  return;
} // end of PulseOutput::update


bool PulseOutput::isActive ()
{
  if (pulseActive_== true)
  {
    return true;
  }
  else
  {
    return false;
  }
} // end of PulseOutput::isActive
