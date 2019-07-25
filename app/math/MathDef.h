#ifndef MATHDEF_H
#define MATHDEF_H

// #include "CartVec.h"
#include "Point.h"

namespace math {

using circle_t = struct Circle {
   Circle(const Point &m, double r)
      : m(m)
      , r(r)
   {
   }
   Point m;
   double r;
};

using edge_t = struct Edge {
   Edge(const Point &start, const Point &end)
      : start(start)
      , end(end)
   {
   }
   Point start;
   Point end;
};

[[nodiscard]] constexpr double toRadians(double x) noexcept
{
   return 0.0174532925 * x;
}

[[nodiscard]] constexpr double toDegrees(double x) noexcept
{
   return 57.2957795130 * x;
}

/// returns 0 <= angle <= 360 degrees
double normalizeDegrees(double x);

} // namespace math

#endif // MATHDEF_H
