/*
Adds the ability to construct a pulse output which, when triggered, generates a
pulse of specific length on the specified output
*/

#ifndef ARDUINO_H
#define ARDUINO_H
#include "Arduino.h"
#endif /* end of include guard: ARDUINO_H */

class PulseOutput
{
  public:
    // constructor
    PulseOutput (
      const char pin,                   // the pin we want to use
      const unsigned long pulseLength,  // the length of the pulse
      const bool pulsePolarity = true   // the polarity of the pulse true: ON = HIGH, OFF = LOW
    );

    void begin ();
    void update ();
    void trigger ();

  private:
    const char pin_;
    const unsigned long pulseLength_;
    const bool pulsePolarity_;
    bool pulseActive_;                  // HIGH when a pulse is currently active
    unsigned long startTime_;           // time the pulse started
}; // end of PulseOutput class
