#ifndef HARDWARE_ACTUATOR_H
#define HARDWARE_ACTUATOR_H

#include "HWdef.h"

#include <cstddef>

namespace hardware {

class Actuator
{
public:
   Actuator(memory_t &memory, size_t index1);
   Actuator(memory_t &memory, size_t index1, size_t index2);
   Actuator(memory_t &memory, size_t index1, size_t index2, size_t index3);
   virtual ~Actuator() = default;

protected:
   memory_t &memory_;
   size_t index1_;
   size_t index2_;
   size_t index3_;
};

} // namespace hardware

#endif // HARDWARE_ACTUATOR_H
