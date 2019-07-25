#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "MathDef.h"
#include "Point.h"
#include "Polygon.h"

#include <vector>

namespace physics {

/// \short Detects collisions between a circle and a polygon, and a circle
/// and another circle.
class CollisionDetector
{
public:
   CollisionDetector() = default;
   virtual ~CollisionDetector() = default;

   /// Tests for collission between a cicle and a polygon.
   bool isColliding(const math::circle_t &c, const math::Polygon &p);
   /// Tests for collission between a circle and a circle.
   /// Collission point is calculated on the line between the circle
   /// centers.
   bool isColliding(const math::circle_t &c1, const math::circle_t &c2);
   const std::vector<Point> &getCollisionPoints() const
   {
      return collisionPoints_;
   }

private:
   std::vector<Point> collisionPoints_;
};

} // namespace physics

#endif // COLLISIONDETECTOR_H
