#ifndef HARDWARE_IOINTERN_H
#define HARDWARE_IOINTERN_H

#include "IObus.h"
#include "IOdef.h"

namespace hardware {

class IOintern
{
public:
   IOintern(IObus_t &IOb);
   virtual ~IOintern() = default;

   void setBOOLout(size_t index, bool value)
   {
      _IO.BOOLout.at(index) = value;
   }
   bool getBOOLin(size_t index) const
   {
      return _IO.BOOLin.at(index);
   }
   void setINTout(size_t index, int value)
   {
      _IO.INTout.at(index) = value;
   }
   int getINTin(size_t index) const { return _IO.INTin.at(index); }

private:
   IObus_t &_IO;
};

} // namespace hardware

#endif // HARDWARE_IOINTERN_H
