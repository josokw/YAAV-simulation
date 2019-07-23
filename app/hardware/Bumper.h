#ifndef HARDWARE_BUMPER_H
#define HARDWARE_BUMPER_H

#include "DoPhysics.h"
#include "Sensor.h"

#include <vector>

namespace utils {
class Logger;
}
class Vehicle;

namespace hardware {

class Bumper : public Sensor, public physics::DoPhysics
{
public:
   Bumper(const Vehicle &vehicle, double startAngle, double endAngle, int n,
          memory_t &memory, size_t index1);
   ~Bumper() = default;

   void process();

private:
   utils::Logger &_logger;
   const Vehicle &_vehicle;
   std::vector<double> _angles;
   int calcSensorOffset(double collisionAngle) const;
};

} // namespace hardware

#endif // HARDWARE_BUMPER_H
