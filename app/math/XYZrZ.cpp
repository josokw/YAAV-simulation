#include "XYZrZ.h"
#include "MathDef.h"

std::ostream &operator<<(std::ostream &os, const XYZrZ &rhs)
{
   os << "XYZrZ[" << rhs.position << ", " << rhs.Rz << "]";

   return os;
}

XYZrZ operator*(const XYZrZ &lhs, double rhs)
{
   return {lhs.position * rhs};
}

XYZrZ operator+(const XYZrZ &lhs, const math::CartVec &rhs)
{
   return {lhs.position + rhs, lhs.Rz};
}

XYZrZ operator-(const XYZrZ &lhs, const math::CartVec &rhs)
{
   return {lhs.position - rhs, lhs.Rz};
}

XYZrZ operator+(const XYZrZ &lhs, double rhs)
{
   return {lhs.position, math::normalizeDegrees(lhs.Rz + rhs)};
}

XYZrZ operator-(const XYZrZ &lhs, double rhs)
{
   return {lhs.position, math::normalizeDegrees(lhs.Rz - rhs)};
}

XYZrZ::XYZrZ(double x, double y, double z, double rz)
   : position{x, y, z}
   , Rz{rz}
{
}

XYZrZ::XYZrZ(const Point &xyz)
   : position{xyz}
   , Rz{0.0}
{
}

XYZrZ::XYZrZ(const Point &xyz, double rz)
   : position{xyz}
   , Rz{rz}
{
}

void XYZrZ::draw() const
{
   glTranslatef(position.get_x(), position.get_y(), position.get_z());
   glRotatef(Rz, 0.0f, 0.0f, 1.0f);
}
