#ifndef PERIODICTASK_H
#define PERIODICTASK_H

#include "Log.h"

#include <chrono>
#include <condition_variable>
#include <exception>
#include <functional>
#include <mutex>
#include <thread>

/// Represents a periodic task, #t in milliseconds.
/// \todo Use chrono, check implementation.
class PeriodicTask
{
public:
   template <typename C, typename F>
   PeriodicTask(C *object, F mf, int t)
      : t_{t}
      , isAlive_{true}
      , isRunning_{false}
      , mutex_{}
      , condition_{}
      , thread_{(std::bind(&PeriodicTask::execute<C, F>, this, object, mf))}
   {
      SET_FNAME("PeriodicTask:PeriodicTask()");
      LOGD("");
   }

   ~PeriodicTask()
   {
      SET_FNAME("PeriodicTask:~PeriodicTask()");
      LOGD("enter dtor");
      {
         std::unique_lock<std::mutex> lock(mutex_);
         condition_.notify_one();
         isAlive_ = false;
         isRunning_ = true;
      }
      thread_.join();
      LOGI("");
   }

   template <typename C, typename F> void execute(C *object, F mf)
   {
      SET_FNAME("PeriodicTask::execute()");
      std::unique_lock<std::mutex> lock(mutex_);
      while (isAlive_) {
         while (!isRunning_) {
            condition_.wait(lock);
         }
         if (isAlive_) {
            lock.unlock();
            const auto timeout{std::chrono::system_clock::now() +
                               std::chrono::milliseconds(t_)};
            try {
               (object->*mf)();
            }
            catch (std::string &x) {
               LOGE(x);
            }
            catch (std::exception &x) {
               LOGE(x.what());
            }
            catch (...) {
               LOGE("UNKNOWN EXCEPTION");
            }
            std::this_thread::sleep_until(timeout);
            lock.lock();
         }
      }
      LOGD("exit");
   }

   void start()
   {
      std::unique_lock<std::mutex> lock(mutex_);
      isRunning_ = true;
      condition_.notify_one();
   }

   void stop()
   {
      std::unique_lock<std::mutex> lock(mutex_);
      isRunning_ = false;
   }

   void startStop()
   {
      if (isRunning_) {
         stop();
      } else {
         start();
      }
   }

private:
   int t_;
   volatile bool isAlive_;
   volatile bool isRunning_;
   std::mutex mutex_;
   std::condition_variable condition_;
   std::thread thread_;
};

#endif // PERIODICTASK_H
