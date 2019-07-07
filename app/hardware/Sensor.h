#ifndef HARDWARE_SENSOR_H
#define HARDWARE_SENSOR_H

#include "HWdef.h"
#include <cstddef>

namespace hardware {

class Sensor
{
public:
   Sensor(memory_t &memory, size_t index1);
   Sensor(memory_t &memory, size_t index1, size_t index2);
   Sensor(memory_t &memory, size_t index1, size_t index2, size_t index3);
   virtual ~Sensor() = default;

protected:
   memory_t &_memory;
   size_t _index1;
   size_t _index2;
   size_t _index3;
};

} // namespace hardware

#endif // HARDWARE_SENSOR_H
