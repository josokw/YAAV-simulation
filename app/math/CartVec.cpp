#include "CartVec.h"
#include "MathDef.h"
#include <iomanip>
#include <ios>
#include <iostream>

double CartVec::eps(1E-8);
const CartVec CartVec::ZERO(0, 0, 0);
const CartVec CartVec::UNIT_X(1, 0, 0);
const CartVec CartVec::UNIT_Y(0, 1, 0);
const CartVec CartVec::UNIT_Z(0, 0, 1);

CartVec::CartVec(double x, double y, double z)
   : _x(x)
   , _y(y)
   , _z(z)
{
}

bool operator==(const CartVec &lhs, const CartVec &rhs)
{
   return fabs(lhs._x - rhs._x) < CartVec::eps &&
          fabs(lhs._y - rhs._y) < CartVec::eps &&
          fabs(lhs._z - rhs._z) < CartVec::eps;
}

bool operator!=(const CartVec &lhs, const CartVec &rhs)
{
   return !(lhs == rhs);
}

CartVec operator+(const CartVec &lhs, const CartVec &rhs)
{
   CartVec temp(lhs);
   return temp += rhs;
}

CartVec operator-(const CartVec &lhs, const CartVec &rhs)
{
   CartVec temp(lhs);
   return temp -= rhs;
}

CartVec operator*(const CartVec &lhs, const CartVec &rhs)
{
   return CartVec(lhs._y * rhs._z - lhs._z * rhs._y,
                  -lhs._x * rhs._z + lhs._z * rhs._x,
                  lhs._x * rhs._y - lhs._y * rhs._x);
}

CartVec operator*(double lhs, const CartVec &rhs)
{
   CartVec temp(rhs);
   return temp *= lhs;
}

CartVec operator*(const CartVec &lhs, double rhs)
{
   CartVec temp(lhs);
   return temp *= rhs;
}

CartVec operator/(const CartVec &lhs, double rhs)
{
   CartVec temp(lhs);
   return temp /= rhs;
}

double CartVec::distance(const CartVec &cv) const
{
   return std::sqrt((_x - cv._x) * (_x - cv._x) +
                    (_y - cv._y) * (_y - cv._y) +
                    (_z - cv._z) * (_z - cv._z));
}

double CartVec::angle(const CartVec &v) const
{
   // Construct the plane containing v and *this;
   // a local CS is constructed with xx in direction *this
   // yy generates other component of v
   // then atan2 for angle calculation is called.
   double xxL = length();

   if (xxL == 0) {
      return 0;
   }
   CartVec zz((*this) * v); // z-Axis
   double zzL = zz.length();
   if (zzL == 0) {
      // v can coincide with *this or can point in the opposite direction!
      if (-v == *this) {
         return math::PI;
      }
      return 0;
   }
   CartVec xx((*this) / xxL); // x-Axis
   zz /= zzL;
   // now zz and xx are orthonormal to each other.
   CartVec yy(zz * xx); // y-Axis
   return atan2(yy.dot(v), xx.dot(v));
}

void CartVec::rotateAroundZ(const double cosPhi, const double sinPhi)
{
   double xtemp = _x;
   _x = cosPhi * _x - sinPhi * _y;
   _y = sinPhi * xtemp + cosPhi * _y;
}

void CartVec::rotateAroundY(const double cosPhi, const double sinPhi)
{
   double xtemp = _x;
   _x = cosPhi * _x + sinPhi * _z;
   _z = -sinPhi * xtemp + cosPhi * _z;
}

void CartVec::rotateAroundX(const double cosPhi, const double sinPhi)
{
   double ytemp = _y;
   _y = cosPhi * _y - sinPhi * _z;
   _z = sinPhi * ytemp + cosPhi * _z;
}

void CartVec::rotateAround(const CartVec &Axis, double cosPhi,
                           double sinPhi)
{
   // An arbitrarily rotation around Axis.
   // Implemented by constructing a new local CS
   // In this CS Axis becomes zz and xx will span the orthogonal
   // component of xx. yy is constructed by a cross product.
   double axisL = Axis.length();
   if (axisL == 0) {
      return; // a rotation around zero-CartVec is *this
   }

   CartVec zz(Axis);
   zz.normalize();    // zz is unit-length
   CartVec xx(*this); // xx and zz are NOT orthogonal !!
   CartVec yy(zz * xx);
   double yyL = yy.length();
   if (yyL == 0) {
      // now we have 2 possibilities
      //	 either the two CartVecs are dependent
      //	 or one of them is zero.
      // Best thing to do: return *this
      return;
   }
   yy /= yyL;
   // now zz and yy are orthonormal to each other.
   xx = yy * zz;
   // so now we have complete orthonormal set
   CartVec NCS(dot(xx), dot(yy), dot(zz)); // New Coordinate System
   NCS.rotateAroundZ(cosPhi, sinPhi);      // do the rotation in New CS
   *this = xx * NCS._x + yy * NCS._y + zz * NCS._z;
}

std::ostream &operator<<(std::ostream &os, const CartVec &rhs)
{
   os << std::setiosflags(std::ios::fixed) << std::setprecision(3) << '['
      << std::setw(5) << rhs._x << ',' << std::setw(5) << rhs._y << ','
      << std::setw(5) << rhs._z << ']';
   return os;
}

std::istream &operator>>(std::istream &is, CartVec &rhs)
{
   char o = '\0';  // '['
   char c1 = '\0'; // ','
   char c2 = '\0'; // ','
   char c = '\0';  // ']'
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;

   is.clear();
   is >> std::ws >> o >> x >> std::ws >> c1 >> y >> std::ws >> c2 >> z >>
      std::ws >> c;
   if ((o != '[') || (c1 != ',') || (c2 != ',') || (c != ']')) {
      is.setstate(std::ios::failbit);
   }
   // Only if everything is ok, output parameter rhs will be changed.
   if (is) {
      rhs = CartVec(x, y, z);
   }
   return is; // Client code should check state of 'is'
}
