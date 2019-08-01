#ifndef MATHDEF_H
#define MATHDEF_H

namespace math {

[[nodiscard]] constexpr double toRadians(double x) noexcept
{
   return 0.0174532925 * x;
}

[[nodiscard]] constexpr double toDegrees(double x) noexcept
{
   return 57.2957795130 * x;
}

/// Returns 0 <= angle <= 360 degrees.
[[nodiscard]] constexpr double normalizeDegrees(double angle)
{
   while (angle > 360) {
      angle -= 360;
   }
   while (angle < 0) {
      angle += 360;
   }
   return angle;
}

} // namespace math

#endif // MATHDEF_H
