//
// Timer.cpp
//
// programmed by George Andrews
//
// This library is the implementation of timing without delay().
//

#include "Arduino.h"
#include "Timer.h"

Timer::Timer(const long interval)
{
  this->Interval = interval;
  this->PreviousMillis = 0;
}

boolean Timer::Wait()
{
  this->CurrentMillis = millis();
  
  if (this->CurrentMillis - this->PreviousMillis >= this->Interval)
  {
    return true;
  }
}
