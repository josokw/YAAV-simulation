#ifndef PHYSICSDEF_H
#define PHYSICSDEF_H

#include "PhysicsState.h"

namespace physics {

const int SIMTIME_MSEC{5};
const double SIMTIME_SEC{0.005};

enum PhysicsStates { CYLOBJ_COLLISION = 0, WALL_COLLISION, PHYSICS_N_STATES };

using PhysicsState_t = PhysicsState<int, PHYSICS_N_STATES>;

} // namespace physics

#endif // PHYSICSDEF_H
