#include "EventQueue.h"
#include "Log.h"
#include <sstream>

EventQueue::EventQueue()
   : _destruct(false)
   , _queue()
   , _mutex()
   , _condition()
   , _thread(std::ref(*this))
{
}

EventQueue::~EventQueue()
{
   SET_FNAME("EventQueue::~EventQueue()");
   std::unique_lock<std::mutex> lock(_mutex);
   _destruct = true;
   _condition.notify_all();
   lock.unlock();
   _thread.join();
   LOGD("");
}

void EventQueue::operator()()
{
   SET_FNAME("EventQueue::operator()");
   try {
      std::unique_lock<std::mutex> lock(_mutex);
      while (not _destruct or not _queue.empty()) {
         while (not _destruct and _queue.empty()) {
            _condition.wait(lock);
         }
         if (not _queue.empty()) {
            int event = _queue.front();
            _queue.pop();
            lock.unlock();
            std::ostringstream msg;
            msg << "event " << event << " processed";
            LOGD(msg.str());
            lock.lock();
         }
      }
   } catch (std::exception &e) {
      LOGE(e.what());
   } catch (...) {
      LOGE("Unknown exception");
   }
}

void EventQueue::post(int event)
{
   SET_FNAME("EventQueue::post()");
   std::unique_lock<std::mutex> lock(_mutex);
   _queue.push(event);
   LOGD("event posted");
   _condition.notify_all();
}
