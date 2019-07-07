#include "XYZrZ.h"
#include "math/MathDef.h"

std::ostream &operator<<(std::ostream &os, const XYZrZ &rhs)
{
   os << "[" << rhs.position << ", " << rhs.Rz << "]";
   return os;
}

XYZrZ operator+(const XYZrZ &lhs, const XYZrZ &rhs)
{
   return XYZrZ(lhs.position + rhs.position, lhs.Rz + rhs.Rz);
}

XYZrZ operator-(const XYZrZ &lhs, const XYZrZ &rhs)
{
   return XYZrZ(lhs.position - rhs.position, lhs.Rz - rhs.Rz);
}

XYZrZ operator*(const XYZrZ &lhs, double rhs)
{
   return XYZrZ(lhs.position * rhs);
}

XYZrZ operator+(const XYZrZ &lhs, const CartVec &rhs)
{
   return XYZrZ(lhs.position + rhs, lhs.Rz);
}

XYZrZ operator-(const XYZrZ &lhs, const CartVec &rhs)
{
   return XYZrZ(lhs.position - rhs, lhs.Rz);
}

XYZrZ operator+(const XYZrZ &lhs, double rhs)
{
   return XYZrZ(lhs.position, math::normalizeDegrees(lhs.Rz + rhs));
}

XYZrZ operator-(const XYZrZ &lhs, double rhs)
{
   return XYZrZ(lhs.position, math::normalizeDegrees(lhs.Rz - rhs));
}

XYZrZ::XYZrZ(double x, double y, double z, double rz)
   : position(x, y, z)
   , Rz(rz)
{
}

XYZrZ::XYZrZ(const CartVec &xyz)
   : position(xyz)
   , Rz(0)
{
}

XYZrZ::XYZrZ(const CartVec &xyz, double rz)
   : position(xyz)
   , Rz(rz)
{
}

void XYZrZ::draw() const
{
   glTranslatef(position.get_x(), position.get_y(), position.get_z());
   glRotatef(Rz, 0, 0, 1);
}
