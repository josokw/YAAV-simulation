#ifndef HARDWARE_IOBUS_H
#define HARDWARE_IOBUS_H

#include <algorithm>
#include <array>
#include <iostream>

namespace hardware {

template <int N_BOOL_IN, int N_BOOL_OUT, int N_INT_IN, int N_INT_OUT>
class IObus
{
public:
   IObus()
      : BOOLin()
      , BOOLout()
      , INTin()
      , INTout()
   {
      std::fill(begin(BOOLin), end(BOOLin), false);
      std::fill(begin(BOOLout), end(BOOLout), false);
      std::fill(begin(INTin), end(INTin), 0);
      std::fill(begin(INTout), end(INTout), 0);
   }
   virtual ~IObus() = default;

   std::array<bool, N_BOOL_IN> BOOLin;
   std::array<bool, N_BOOL_OUT> BOOLout;
   std::array<int, N_INT_IN> INTin;
   std::array<int, N_INT_OUT> INTout;
};

template <typename T> class IRQstatus
{
public:
   typedef void (T::*pFunction_t)();
   IRQstatus()
      : _current(false)
      , _previous(false)
      , _pFunction(nullptr)
   {
   }
   virtual ~IRQstatus() {}
   void trigger(bool value)
   {
      _previous = _current;
      _current = value;
   }
   bool get() const { return _current; }
   bool risingEdge() const { return (_current && !_previous); }
   void setISR(pFunction_t pF) { _pFunction = pF; }
   void react(T *obj)
   {
      if (_pFunction != nullptr && risingEdge()) {
         (obj->*_pFunction)();
      }
   }

private:
   bool _current;
   bool _previous;
   pFunction_t _pFunction;
};

template <typename T, int N_IRQ_IN> class IRQbus
{
public:
   IRQbus()
      : _IRQin()
   {
      std::fill(begin(_IRQin), end(_IRQin), IRQstatus<T>());
   }
   virtual ~IRQbus() = default;

   IRQstatus<T> &operator[](size_t index) { return _IRQin[index]; }
   const IRQstatus<T> &operator[](size_t index) const
   {
      return _IRQin[index];
   }

private:
   std::array<IRQstatus<T>, N_IRQ_IN> _IRQin;
};

} // namespace hardware

#endif // HARDWARE_IOBUS_H
