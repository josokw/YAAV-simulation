#include "Edge.h"
#include "CartVec.h"

Point math::Edge::getClosestPoint(const Point &point) const
{
   
   CartVec v{getEnd() - getStart()};
   CartVec w{point - getStart()};
   double wDotv{w.dot(v)};
   double t{wDotv / v.dot(v)};

   if (t < 0) {
      t = 0;
   }
   if (t > 1) {
      t = 1;
   }

   return getStart() + v * t;
}
