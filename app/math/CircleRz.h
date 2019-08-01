#ifndef CIRCLERZ_H
#define CIRCLERZ_H

#include "CartVec.h"
#include "Circle.h"
#include "MathDef.h"

namespace math {

/// Represents a rotating circle.
/// \bug + and - operator for CartVec does not compile, inheritance problem?
class CircleRz : public math::Circle
{
   friend std::ostream &operator<<(std::ostream &os, const math::CircleRz &rhs);
   friend math::CircleRz operator+(const math::CircleRz &lhs,
                                   math::CartVec &rhs);
   friend math::CircleRz operator-(const math::CircleRz &lhs,
                                   math::CartVec &rhs);
   friend math::CircleRz operator+(const math::CircleRz &lhs, double rhs);
   friend math::CircleRz operator-(const math::CircleRz &lhs, double rhs);

public:
   CircleRz()
      : Circle{}
   {
   }

   CircleRz(const Point &center, double radius = 1.0, double Rz = 0.0)
      : Circle{center, radius}
      , Rz_{Rz}
   {
   }

   double getRz() const { return Rz_; }
   void setRz(double Rz) { Rz_ = Rz; }
   std::tuple<math::Point, double, double> getCenterRadiusRz() const
   {
      return {center_, radius_, Rz_};
   }
   math::CartVec heading() const
   {
      return {cos(math::toRadians(Rz_)), sin(math::toRadians(Rz_))};
   }

    /// Translation: crz += cv
   math::CircleRz &operator+=(const CartVec &rhs);
   /// Translation: crz -= cv
   math::CircleRz &operator-=(const CartVec &rhs);
   /// Rotation: crz += deltaRz
   math::CircleRz &operator+=(double rhs);
   /// Rotation: crz -= deltaRz
   math::CircleRz &operator-=(double rhs);

private:
   double Rz_{0.0};
};

} // namespace math

#endif
