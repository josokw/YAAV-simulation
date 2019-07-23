#ifndef HARDWARE_TIMER_H
#define HARDWARE_TIMER_H

#include "DoPhysics.h"

namespace hardware {

enum class mode_t { ONE_SHOT, PERIODIC };

template <typename T> class Timer : public physics::DoPhysics
{
public:
   typedef void (T::*pFunction_t)();
   Timer(T *obj)
      : _elapsedTime_ms(0L)
      , _isRunning(false)
      , _mode(mode_t::ONE_SHOT)
      , _time(0L)
      , _pObj(obj)
      , _pFunction(nullptr)
   {
   }
   Timer(const Timer &other) = delete;
   Timer &operator=(const Timer &other) = delete;
   virtual ~Timer() = default;

   void process() override
   {
      if (_isRunning) {
         _elapsedTime_ms += PHYSICS_SIMTIME_MSEC;
         if (_elapsedTime_ms >= _time) {
            if (_pFunction != nullptr) {
               (_pObj->*_pFunction)();
            }
            _elapsedTime_ms = 0L;
            switch (_mode) {
               case mode_t::ONE_SHOT:
                  _isRunning = false;
                  break;
               case mode_t::PERIODIC:
                  _isRunning = true;
                  break;
               default:
                  _isRunning = false;
                  break;
            }
         }
      }
   }
   void setTime(long long time, mode_t mode)
   {
      _time = time;
      _mode = mode;
   }
   void setISR(pFunction_t pF) { _pFunction = pF; }
   void start() { _isRunning = true; }
   long long getElapsedTime() const { return _elapsedTime_ms; }

private:
   long long _elapsedTime_ms;
   bool _isRunning;
   mode_t _mode;
   long long _time;
   T *_pObj;
   pFunction_t _pFunction;
};

} // namespace hardware

#endif // HARDWARE_TIMER_H
