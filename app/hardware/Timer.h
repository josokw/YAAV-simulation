#ifndef HARDWARE_TIMER_H
#define HARDWARE_TIMER_H

#include "DoPhysics.h"

#include <atomic>

namespace hardware {

enum class mode_t { ONE_SHOT, PERIODIC };

template <typename T> class Timer : public physics::DoPhysics
{
public:
   using pFunction_t = void (T::*)();

   Timer(T *obj)
      : elapsedTime_ms_(0L)
      , isRunning_(false)
      , mode_(mode_t::ONE_SHOT)
      , time_(0L)
      , pObj_(obj)
      , pFunction_(nullptr)
   {
   }
   Timer(const Timer &) = delete;
   Timer &operator=(const Timer &) = delete;
   ~Timer() override = default;

   void process() override
   {
      if (isRunning_) {
         elapsedTime_ms_ += physics::SIMTIME_MSEC;
         if (elapsedTime_ms_ >= time_) {
            if (pFunction_ != nullptr) {
               (pObj_->*pFunction_)();
            }
            elapsedTime_ms_ = 0L;
            switch (mode_) {
               case mode_t::ONE_SHOT:
                  isRunning_ = false;
                  break;
               case mode_t::PERIODIC:
                  isRunning_ = true;
                  break;
               default:
                  isRunning_ = false;
                  break;
            }
         }
      }
   }
   void setTime(long long time, mode_t mode)
   {
      time_ = time;
      mode_ = mode;
   }
   void setISR(pFunction_t pF) { pFunction_ = pF; }
   void start() { isRunning_ = true; }
   long long getElapsedTime() const { return elapsedTime_ms_; }

private:
   long long elapsedTime_ms_;
   std::atomic<bool> isRunning_;
   mode_t mode_;
   long long time_;
   T *pObj_;
   pFunction_t pFunction_;
};

} // namespace hardware

#endif // HARDWARE_TIMER_H
