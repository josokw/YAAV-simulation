#ifndef EDGE_H
#define EDGE_H

#include "Point.h"

namespace math {

class Edge
{
public:
   Edge(const Point &start, const Point &end)
      : start_{start}
      , end_{end}
   {
   }

   Point getStart() const { return start_; }
   Point getEnd() const { return end_; }
   double length() const { return start_.distance(end_); } 
   Point getClosestPoint(const Point &point) const;

private:
   Point start_;
   Point end_;
};

} // namespace math

#endif
