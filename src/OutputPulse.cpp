/*
Adds the ability to construct a pulse output which, when triggered, generates a
pulse of specific length on the specified output
*/

#include <OutputPulse.h>

/* constructors */
// constructor for pin, pulseLength and pulsePolarity
OutputPulse::OutputPulse (
  const char pin,
  const unsigned long pulseLength,
  const bool pulsePolarity
)
{
  startTime_ = 0;
  pin_ = pin;
  pulseLength_ = pulseLength;
  pulsePolarity_ = pulsePolarity;
} // end of OutputPulse::OutputPulse

/* methods */
void OutputPulse::begin()
{
  // set the pin as output
  pinMode(pin_, OUTPUT);
  // set the initial output value based on pulsePolarity
  digitalWrite(pin_, !pulsePolarity_);
} // end of OutputPulse::begin


/*
@brief Triggers an output pulse
*/
void OutputPulse::trigger()
{
  // set the start time
  startTime_ = millis();
  // set the variable to indicate a pulse is currently active
  pulseActive_ = true;
  // activate the output
  digitalWrite(pin_, pulsePolarity_);
} // end of OutputPulse::trigger


void OutputPulse::update()
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
} // end of OutputPulse::update


bool OutputPulse::isActive ()
{
  if (pulseActive_== true)
  {
    return true;
  }
  else
  {
    return false;
  }
} // end of OutputPulse::isActive
