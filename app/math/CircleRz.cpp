#include "CircleRz.h"

#include <iostream>

namespace math {

std::ostream &operator<<(std::ostream &os, const math::CircleRz &rhs)
{
   os << "CrZ[" << static_cast<Circle>(rhs) << ", " << rhs.Rz_ << "]";

   return os;
}

math::CircleRz operator+(const math::CircleRz &lhs, const math::CartVec &rhs)
{
   return {lhs.getCenter() + rhs, lhs.getRadius(), lhs.getRz()};
}

math::CircleRz operator-(const math::CircleRz &lhs, const math::CartVec &rhs)
{
   return {lhs.getCenter() - rhs, lhs.getRadius(), lhs.getRz()};
}

math::CircleRz &math::CircleRz::operator+=(const CartVec &rhs)
{
   center_ += rhs;
   return *this;
}

math::CircleRz &math::CircleRz::operator-=(const CartVec &rhs)
{
   center_ -= rhs;
   return *this;
}

math::CircleRz &math::CircleRz::operator+=(double rhs)
{
   Rz_ += rhs;
   Rz_ = math::normalizeDegrees(Rz_);
   return *this;
}
/// Rotation: crz -= deltaRz
math::CircleRz &math::CircleRz::operator-=(double rhs)
{
   Rz_ -= rhs;
   Rz_ = math::normalizeDegrees(Rz_);
   return *this;
}

} // namespace math
