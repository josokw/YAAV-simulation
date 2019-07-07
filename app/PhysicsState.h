#ifndef PHYSICSSTATE_H
#define PHYSICSSTATE_H

#include <algorithm>
#include <array>

template <typename T, int SIZE> class PhysicsState
{
public:
   PhysicsState()
   {
      std::fill(physicsState.begin(), physicsState.end(), 0.0);
   }
   T &operator[](int index) { return physicsState[index]; }
   const T &operator[](int index) const { return physicsState[index]; }

private:
   std::array<T, SIZE> physicsState;
};

#endif // PHYSICSSTATE_H
