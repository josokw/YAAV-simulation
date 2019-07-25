#ifndef DOPHYSICS_H
#define DOPHYSICS_H

#include "PhysicsDef.h"
#include "XYZrZ.h"

#include <vector>

namespace physics {

class DoPhysics
{
public:
   DoPhysics() = default;
   virtual ~DoPhysics() = default;

   virtual void process() = 0;

   static PhysicsState_t physicsState;
   // static std::vector<XYZrZ> vehicleCollisions;
   static std::vector<CartVec> vehicleCollisions;
};

} // namespace physics

#endif // DOPHYSICS_H
