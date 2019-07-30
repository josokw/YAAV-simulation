#ifndef ORIENTATIONCONE_H
#define ORIENTATIONCONE_H

#include "CartVec.h"
#include "Drawable.h"
#include "XYZrZ.h"

#include <array>

/// Draws an orientation cone in a specific color.
/// \bug Calculations for other positions not correct.
class OrientationCone : public Drawable
{
   friend OrientationCone operator*(const OrientationCone &lhs, double rhs);
   friend OrientationCone operator*(double lhs, const OrientationCone &rhs);

public:
   static const OrientationCone OcX;
   static const OrientationCone OcY;
   static const OrientationCone OcZ;

   OrientationCone(const std::array<float, 3> &rgb, const Point &position,
                   const math::CartVec &orientation);
   OrientationCone(const OrientationCone &ocone);
   OrientationCone &operator=(const OrientationCone &) = delete;
   ~OrientationCone() override;

   void draw() const override;

private:
   std::array<float, 3> rgb_;
   Point position_;
   math::CartVec orientation_;
   GLUquadricObj *pBody_;
};

#endif // ORIENTATIONCONE_H
