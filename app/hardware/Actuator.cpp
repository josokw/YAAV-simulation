#include "Actuator.h"
#include "Memory.h"

hardware::Actuator::Actuator(memory_t &memory, size_t index1)
   : memory_{memory}
   , index1_{index1}
   , index2_{0}
   , index3_{0}
{
}

hardware::Actuator::Actuator(memory_t &memory, size_t index1,
                             size_t index2)
   : memory_{memory}
   , index1_{index1}
   , index2_{index2}
   , index3_{0}
{
}

hardware::Actuator::Actuator(memory_t &memory, size_t index1,
                             size_t index2, size_t index3)
   : memory_{memory}
   , index1_{index1}
   , index2_{index2}
   , index3_{index3}
{
}
