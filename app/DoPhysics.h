#ifndef DOPHYSICS_H
#define DOPHYSICS_H

#include "PhysicsDef.h"
#include "math/XYZrZ.h"
#include <vector>

namespace physics {

class DoPhysics
{
public:
   DoPhysics() {}
   virtual ~DoPhysics() = default;

   virtual void process() = 0;

   static PhysicsState_t physicsState;
   static std::vector<XYZrZ> vehicleCollisions;
};

} // namespace physics

#endif // DOPHYSICS_H
