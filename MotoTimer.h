/********************************************************************************************************************************
Classe utilisee dans la classe AvoidDelay.
**Provient de:
https://github.com/MicroBahner/MobaTools
*********************************************************************************************************************************
MoToTimer.h - part of MobaTools
Class MoToTimer - Timer management for time delays in the loop
/*
    MoToTimer myTimer()                 // Create Timerobject
    void setTime( unsigned long value ) // Start Timer with new time value
    void restart()                      // Restart Timer with last set time value ( setTime )
    bool running()                      // True while timer is running
    bool expired()                      // Only 'true' at the first call after timer expiry.
    void stop()                         // Stopping the timer prematurely
    unsigned long getRemain()           // Get remaining time if timer is running, 0 otherwise
    unsigned long getElapsed()          // Get elapsed time if timer is running, last value of setTime otherwise
    unsigned long getRuntime()          // Get last value of setTime

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef MOTOTIMER_H
#define MOTOTIMER_H
class MoToTimerRop  // Ram optimized version
{
private:
  static constexpr byte RUNNING = 0b1;
  static constexpr byte NOTEXPIRED = 0b10;
  byte active;  // Bit0: Timer is running, Bit 1: not expired Flag
  long endtime;

public:
  MoToTimerRop() {
    active = 0;
  }

  void setTime(long wert) {
    endtime = (long)millis() + ((long)wert > 0 ? wert : 1);
    active = RUNNING | NOTEXPIRED;  // set running and !expired flag
  }

  bool running() {
    if (active & RUNNING) active &= ~RUNNING | (endtime - (long)millis() > 0);
    return active & RUNNING;
  }

  bool expired() {  // event 'timer expired'
    // this event is cleared after call of this method
    if (running() || active == 0) return false;
    else active = 0;
    return true;
  }

  void stop() {
    active = 0;
  }

  long getTime() {
    // return remaining time
    if (running()) return endtime - (long)millis();
    else return 0;
  }
};
#endif
