#include "CollisionDetector.h"
#include "Log.h"

#include <sstream>

bool physics::CollisionDetector::isColliding(const math::Circle &c,
                                             const math::Polygon &p)
{
   SET_FNAME("physics::CollisionDetector::isColliding(circle, polygon)");
   collisionPoints_.clear();
   const std::vector<Point> &vertices(p.getVertices());
   size_t nCollisions{0};
   // {
   //    std::ostringstream msg;
   //    msg << p;
   //    LOGD(msg.str());
   // }
   for (size_t vertexID = 0; vertexID < vertices.size(); ++vertexID) {
      Point closestPoint(p.getClosestPointToEdge(vertexID, c.getCenter()));
      {
         std::ostringstream msg;
         msg << "closestPoint = " << closestPoint;
         LOGD(msg.str());
      }
      double distance = closestPoint.distance(c.getCenter());
      if (distance <= c.getRadius()) {
         ++nCollisions;
         collisionPoints_.push_back(closestPoint);
         {
            std::ostringstream msg;
            msg << "#" << nCollisions << " vertexID = " << vertexID
                << " WCS: " << closestPoint;
            LOGD(msg.str());
         }
      }
   }
   return nCollisions > 0;
}

bool physics::CollisionDetector::isColliding(const math::Circle &c1,
                                             const math::Circle &c2)
{
   SET_FNAME("physics::CollisionDetector::isColliding(circle, circle)");
   collisionPoints_.clear();
   math::CartVec delta{c2.getCenter() - c1.getCenter()};
   if (delta.length() <= (c1.getRadius() + c2.getRadius())) {
      Point collisionPoint{
         c1.getCenter() +
         delta * ((c1.getRadius() + c2.getRadius()) / c1.getRadius())};
      collisionPoints_.push_back(collisionPoint);
      {
         std::ostringstream msg;
         msg << "WCS collision point: " << collisionPoint;
         LOGD(msg.str());
      }
      return true;
   }
   return false;
}
