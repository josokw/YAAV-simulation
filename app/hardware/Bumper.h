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
   ~Bumper() override = default;

   void process() override;

private:
   utils::Logger &logger_;
   const Vehicle &vehicle_;
   std::vector<double> angles_;

   int calcSensorOffset(double collisionAngle) const;
};

} // namespace hardware

#endif // HARDWARE_BUMPER_H
