#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

class EventQueue
{
public:
   EventQueue();
   ~EventQueue();

   void operator()();
   void post(int event);

private:
   bool _destruct;
   std::queue<int> _queue;
   std::mutex _mutex;
   std::condition_variable _condition;
   std::thread _thread;
};

#endif // EVENTQUEUE_H
