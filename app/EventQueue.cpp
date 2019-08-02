#include "EventQueue.h"
#include "Log.h"

#include <sstream>

EventQueue::EventQueue()
   : stop_{false}
   , queue_{}
   , mutex_{}
   , condition_{}
   , handleEvents_{[this]() { handle(); }}
{
}

EventQueue::~EventQueue()
{
   SET_FNAME("EventQueue::~EventQueue()");
   std::unique_lock<std::mutex> lock(mutex_);
   stop_ = true;
   condition_.notify_all();
   lock.unlock();
   handleEvents_.join();
   LOGD("");
}

void EventQueue::handle()
{
   SET_FNAME("EventQueue::handle()");
   try {
      std::unique_lock<std::mutex> lock(mutex_);
      while (not stop_ or not queue_.empty()) {
         while (not stop_ and queue_.empty()) {
            condition_.wait(lock);
         }
         if (not queue_.empty()) {
            int event = queue_.front();
            queue_.pop();
            lock.unlock();
            {
               std::ostringstream msg;
               msg << "event " << event << " processed";
               LOGD(msg.str());
            }
            lock.lock();
         }
      }
   }
   catch (std::exception &e) {
      LOGE(e.what());
   }
   catch (...) {
      LOGE("Unknown exception");
   }
}

void EventQueue::post(int event)
{
   SET_FNAME("EventQueue::post()");
   std::unique_lock<std::mutex> lock(mutex_);
   queue_.push(event);
   LOGD("event posted");
   condition_.notify_all();
}
