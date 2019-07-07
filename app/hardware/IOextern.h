#ifndef HARDWARE_IOEXTERN_H
#define HARDWARE_IOEXTERN_H

#include "IObus.h"
#include "IOdef.h"

namespace hardware {

class IOextern
{
public:
   IOextern(IObus_t &IOb);
   virtual ~IOextern() = default;

   void setBOOLin(size_t index, bool value)
   {
      _IO.BOOLin.at(index) = value;
   }
   bool getBOOLout(size_t index) const { return _IO.BOOLout.at(index); }
   void setINTin(size_t index, int value) { _IO.INTin.at(index) = value; }
   int getINTout(size_t index) const { return _IO.INTout.at(index); }

private:
   IObus_t &_IO;
};

} // namespace hardware

#endif // HARDWARE_IOEXTERN_H
