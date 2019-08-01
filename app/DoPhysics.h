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

   inline static physics::PhysicsState_t physicsState;
   inline static std::vector<math::CartVec> vehicleCollisions;
};

} // namespace physics

#endif // DOPHYSICS_H
