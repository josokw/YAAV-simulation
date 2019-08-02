#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

/// Reponsible for handling queued events (int type).
class EventQueue
{
public:
   EventQueue();
   ~EventQueue();

   void handle();
   void post(int event);

private:
   std::atomic<bool> stop_;
   std::queue<int> queue_;
   std::mutex mutex_;
   std::condition_variable condition_;
   std::thread handleEvents_;
};

#endif // EVENTQUEUE_H
