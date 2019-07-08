#ifndef MATHDEF_H
#define MATHDEF_H

#include "CartVec.h"

namespace math {

using circle_t = struct Circle {
   Circle(const CartVec &m, double r)
      : m(m)
      , r(r)
   {
   }
   CartVec m;
   double r;
};

using edge_t = struct Edge {
   Edge(const CartVec &start, const CartVec &end)
      : start(start)
      , end(end)
   {
   }
   CartVec start;
   CartVec end;
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
