#include "MathDef.h"

double math::normalizeDegrees(double x)
{
   while (x > 360)
      x -= 360;
   while (x < 0)
      x += 360;
   return x;
}
