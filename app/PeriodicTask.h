#ifndef PERIODICTASK_H
#define PERIODICTASK_H

#include "Log.h"
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <exception>

/// Represents a periodic task.
class PeriodicTask
{
public:
   template <typename C, typename F>
   PeriodicTask(C *object, F mf, int t)
      : t(t)
      , isAlive(true)
      , isRunning(false)
      , mutex()
      , condition()
      , thread(
           (boost::bind(&PeriodicTask::execute<C, F>, this, object, mf)))
   {
      SET_FNAME("PeriodicTask:PeriodicTask()");
      LOGD("");
   }

   ~PeriodicTask()
   {
      SET_FNAME("PeriodicTask:~PeriodicTask()");
      LOGD("enter dtor");
      boost::mutex::scoped_lock lock(mutex);
      condition.notify_one();
      isAlive = false;
      isRunning = true;
      lock.unlock();
      thread.join();
      LOGI("");
   }

   template <typename C, typename F> void execute(C *object, F mf)
   {
      SET_FNAME("PeriodicTask::execute()");
      boost::mutex::scoped_lock lock(mutex);
      while (isAlive) {
         while (!isRunning) {
            condition.wait(lock);
         }
         if (isAlive) {
            lock.unlock();
            const boost::system_time timeout(
               boost::get_system_time() +
               boost::posix_time::milliseconds(t));
            try {
               (object->*mf)();
            } catch (std::string &x) {
               LOGE(x);
            } catch (std::exception &x) {
               LOGE(x.what());
            } catch (...) {
               LOGE("UNKNOWN EXCEPTION");
            }
            boost::this_thread::sleep(timeout);
            lock.lock();
         }
      }
      LOGD("exit");
   }

   void start()
   {
      boost::mutex::scoped_lock lock(mutex);
      isRunning = true;
      condition.notify_one();
   }

   void stop()
   {
      boost::mutex::scoped_lock lock(mutex);
      isRunning = false;
   }

   void startStop()
   {
      if (isRunning) {
         stop();
      } else {
         start();
      }
   }

private:
   int t;
   volatile bool isAlive;
   volatile bool isRunning;
   boost::mutex mutex;
   boost::condition_variable condition;
   boost::thread thread;
};

#endif // PERIODICTASK_H
