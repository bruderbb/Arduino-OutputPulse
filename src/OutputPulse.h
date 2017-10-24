/*
Adds the ability to construct a pulse output which, when triggered, generates a
pulse of specific length on the specified output
*/
#ifndef OutputPulse_H
#define OutputPulse_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#ifndef OUTPUTPULSE_DEBUG
// uncomment the following line to enable serial debug output messages
//#define OUTPUTPULSE_DEBUG
#endif

class OutputPulse
{
  public:
    // constructors
    OutputPulse (
      const uint8_t    pin,                   // the pin we want to use
      const uint32_t   pulseLength    = 25,   // the length of the pulse
      const bool       pulsePolarity  = true  // the polarity of the pulse true: ON = HIGH, false: ON = LOW
    );

    // methods
    void begin ();
    void update ();
    void trigger ();
    bool isActive ();

  private:
    uint8_t   pin_;
    uint32_t  pulseLength_;
    bool      pulsePolarity_;
    bool      pulseActive_;    // HIGH when a pulse is currently active
    uint32_t  startTime_;      // time the pulse started
}; // end of OutputPulse class
#endif // end of Include Guard OutputPulse_h
