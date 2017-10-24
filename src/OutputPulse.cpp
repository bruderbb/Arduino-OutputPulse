/*
Adds the ability to construct a pulse output which, when triggered, generates a
pulse of specific length on the specified output
*/

#include <OutputPulse.h>

/* constructors */
// constructor for pin, pulseLength and pulsePolarity
OutputPulse::OutputPulse(
  const uint8_t   pin,
  const uint32_t  pulseLength,
  const bool      pulsePolarity
)
{
  startTime_      = 0;
  pin_            = pin;
  pulseLength_    = pulseLength;
  pulsePolarity_  = pulsePolarity;
} // end of OutputPulse::OutputPulse

/* methods */
void OutputPulse::begin()
{
  #ifdef OUTPUTPULSE_DEBUG
  Serial.print    ("Pin ");
  Serial.print    (pin_);
  Serial.println  (" now defined as OutputPulse");
  #endif
  // set the initial output value based on pulsePolarity
  digitalWrite(pin_, !pulsePolarity_);
} // end of OutputPulse::begin


/*
@brief Triggers an output pulse
*/
void OutputPulse::trigger()
{
  // pulse got triggered
  #ifdef OUTPUTPULSE_DEBUG
  Serial.println  ("Pulse triggered");
  #endif
  // set the start time
  startTime_ = millis();
  #ifdef OUTPUTPULSE_DEBUG
  Serial.print    ("startTime_ is: ");
  Serial.println  (startTime_);
  #endif
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

  // a variable for saving the current time
  uint32_t now = millis();

  // detect millis counter overflow (value is smaller than startTime_)
  if (now < startTime_)
  {
    // reset the startTime_ to current
    startTime_ = millis();
    #ifdef OUTPUTPULSE_DEBUG
    Serial.print    ("Millis Counter Overflow. New startTime_ is: ");
    Serial.println  (startTime_);
    #endif

    return;
    // worst case scenario: the output pulse is double the pulseLength (minus 1)
  }


  // if the stop time has been reached turn the pulse OFF
  if ((now - startTime_) >= pulseLength_)
  {
    #ifdef OUTPUTPULSE_DEBUG
    Serial.print    ("Stop time reached after (ms): ");
    Serial.println  (now - startTime_);
    #endif
    // reset the output pin
    digitalWrite(pin_, !pulsePolarity_);
    // reset the active status
    pulseActive_ = false;
  }
  return;
} // end of OutputPulse::update


bool OutputPulse::isActive ()
{
  return pulseActive_;
} // end of OutputPulse::isActive
