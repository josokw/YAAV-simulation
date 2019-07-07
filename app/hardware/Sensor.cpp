#include "Sensor.h"
#include "Memory.h"

hardware::Sensor::Sensor(memory_t &memory, size_t index1)
   : _memory(memory)
   , _index1(index1)
   , _index2(0)
   , _index3(0)
{
}

hardware::Sensor::Sensor(memory_t &memory, size_t index1, size_t index2)
   : _memory(memory)
   , _index1(index1)
   , _index2(index2)
   , _index3(0)
{
}

hardware::Sensor::Sensor(memory_t &memory, size_t index1, size_t index2,
                         size_t index3)
   : _memory(memory)
   , _index1(index1)
   , _index2(index2)
   , _index3(index3)
{
}
