#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "math/CartVec.h"
#include "math/MathDef.h"
#include "math/Polygon.h"
#include <vector>

namespace physics {
/// @short Detects collisions between a circle and a polygon, and a circle
/// and another circle.
class CollisionDetector
{
public:
   CollisionDetector();
   virtual ~CollisionDetector() = default;

   /// Tests for collission between a cicle and a polygon.
   bool isColliding(const math::circle_t &c, const math::Polygon &p);
   /// Tests for collission between a circle and a circle.
   /// Collission point is calculated on the line between the circle
   /// centers.
   bool isColliding(const math::circle_t &c1, const math::circle_t &c2);
   const std::vector<CartVec> &getCollisionPoints() const
   {
      return m_collisionPoints;
   }

private:
   std::vector<CartVec> m_collisionPoints;
};

} // namespace physics

#endif // COLLISIONDETECTOR_H
