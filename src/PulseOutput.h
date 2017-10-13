/*
Adds the ability to construct a pulse output which, when triggered, generates a
pulse of specific length on the specified output
*/
#ifndef PULSEOUTPUT_H
#define PULSEOUTPUT_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class PulseOutput
{
  public:
    // constructors
    PulseOutput (
      const char pin                    // the pin we want to use
    );

    PulseOutput (
      const char pin,                   // the pin we want to use
      const unsigned long pulseLength   // the length of the pulse
    );

    PulseOutput (
      const char pin,                   // the pin we want to use
      const unsigned long pulseLength,  // the length of the pulse
      const bool pulsePolarity = true   // the polarity of the pulse true: ON = HIGH, false: ON = LOW
    );

    // methods
    void begin ();
    void update ();
    void trigger ();
    bool isActive ();

  private:
    char pin_;
    unsigned long pulseLength_;
    bool pulsePolarity_;
    bool pulseActive_;                  // HIGH when a pulse is currently active
    unsigned long startTime_;           // time the pulse started
}; // end of PulseOutput class
#endif // end of Include Guard PulseOutput_h
