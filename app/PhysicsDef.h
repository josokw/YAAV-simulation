#ifndef PHYSICSDEF_H
#define PHYSICSDEF_H

#include "PhysicsState.h"

#define PHYSICS_SIMTIME_MSEC 5
#define PHYSICS_SIMTIME_SEC 0.005

enum PhysicsStates {
   CYLOBJ_COLLISION = 0,
   WALL_COLLISION,
   PHYSICS_N_STATES
};

namespace physics {
// typedef PhysicsState<double, PHYSICS_N_STATES> PhysicsState_t;
typedef PhysicsState<int, PHYSICS_N_STATES> PhysicsState_t;
}

#endif // PHYSICSDEF_H
