#ifndef EDGE_H
#define EDGE_H

#include "Point.h"

namespace math {

class Edge
{
public:
   Edge(const math::Point &start, const math::Point &end)
      : start_{start}
      , end_{end}
   {
   }

   math::Point getStart() const { return start_; }
   math::Point getEnd() const { return end_; }
   double length() const { return start_.distance(end_); } 
   math::Point getClosestPoint(const math::Point &point) const;

private:
   math::Point start_;
   math::Point end_;
};

} // namespace math

#endif
