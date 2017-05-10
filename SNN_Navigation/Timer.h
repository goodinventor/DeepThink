//
// Timer.h
//
// programmed by George Andrews
//
// This library is the implementation of timing without delay().
//

#ifndef Timer_h
#define Timer_h

#include "Arduino.h"

class Timer
{
  public:
    //
    // variables
    //
  
    // interval for the event
    const long Interval;
  
    //
    // functions
    //
    
    // class constructor
    Timer(const long interval);
    
    // time function
    boolean Wait();
  
  private:
    //
    // variables
    //
    
    // stores last time of update
    unsigned long PreviousMillis;
    
    // current time
    unsigned long CurrentMillis;
};

#endif
