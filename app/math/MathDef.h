#ifndef MATHDEF_H
#define MATHDEF_H

#include "CartVec.h"

namespace math {

typedef struct Circle {
   Circle(const CartVec &m, double r)
      : m(m)
      , r(r)
   {
   }
   CartVec m;
   double r;
} circle_t;

typedef struct Edge {
   Edge(const CartVec &start, const CartVec &end)
      : start(start)
      , end(end)
   {
   }
   CartVec start;
   CartVec end;
} edge_t;

const double PI = 3.1415926535;

inline double toRadians(double x)
{
   return 0.0174532925 * x;
}

inline double toDegrees(double x)
{
   return 57.2957795130 * x;
}

/// returns 0 <= angle <= 360 degrees
double normalizeDegrees(double x);

} // namespace math

#endif // MATHDEF_H
