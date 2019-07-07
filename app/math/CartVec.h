#ifndef CARTVEC_H
#define CARTVEC_H

#include <cmath>
#include <iosfwd>

/// Class 'CartVec' represents a Cartesian vector [x,y,z] in 3D space.
/// @short Cartesian vector in 3D space.
class CartVec
{
   /// Testing for equality.
   /// @see CartVec::eps
   friend bool operator==(const CartVec &lhs, const CartVec &rhs);
   friend bool operator!=(const CartVec &lhs, const CartVec &rhs);
   /// Add 2 Cartvec's.
   friend CartVec operator+(const CartVec &lhs, const CartVec &rhs);
   /// Subtract 2 Cartvec's.
   friend CartVec operator-(const CartVec &lhs, const CartVec &rhs);
   /// Calculates cross product.
   friend CartVec operator*(const CartVec &lhs, const CartVec &rhs);
   /// Multiplication by a scalar.
   friend CartVec operator*(double lhs, const CartVec &rhs);
   /// Multiplication by a scalar.
   friend CartVec operator*(const CartVec &lhs, double rhs);
   /// Division by a scalar.
   friend CartVec operator/(const CartVec &lhs, double rhs);
   /// Output format: [x,y,z]
   friend std::ostream &operator<<(std::ostream &out, const CartVec &rhs);
   /// Input format: [x,y,z]  extra whitespaces allowed
   friend std::istream &operator>>(std::istream &is, CartVec &rhs);

public:
   static double eps;
   static const CartVec ZERO;
   static const CartVec UNIT_X;
   static const CartVec UNIT_Y;
   static const CartVec UNIT_Z;

   CartVec()
      : CartVec(0.0, 0.0, 0.0)
   {
   }
   CartVec(double _x, double _y, double _z);
   CartVec(const CartVec &other) = default;
   virtual ~CartVec() = default;

   double get_x() const { return _x; }
   double get_y() const { return _y; }
   double get_z() const { return _z; }
   void set_x(double x) { _x = x; }
   void set_y(double y) { _y = y; }
   void set_z(double z) { _z = z; }

   /// Unary + operator
   CartVec operator+() const { return *this; }
   /// Unary - operator
   CartVec operator-() const { return CartVec(-_x, -_y, -_z); }
   /// Compound assignment operator [x,y,z] += [a,b,c]
   CartVec &operator+=(const CartVec &rhs)
   {
      _x += rhs._x;
      _y += rhs._y;
      _z += rhs._z;
      return *this;
   }
   /// [x,y,z] -= [a,b,c]
   CartVec &operator-=(const CartVec &rhs)
   {
      _x -= rhs._x;
      _y -= rhs._y;
      _z -= rhs._z;
      return *this;
   }
   /// [x,y,z] *= s
   CartVec &operator*=(double rhs)
   {
      _x *= rhs;
      _y *= rhs;
      _z *= rhs;
      return *this;
   }
   /// [x,y,z] /= s
   CartVec &operator/=(double rhs)
   {
      _x /= rhs;
      _y /= rhs;
      _z /= rhs;
      return *this;
   }

   /// Calculates length: ||vector||
   double length() const { return std::sqrt(_x * _x + _y * _y + _z * _z); }
   /// Distance to other end point of a CartVec.
   double distance(const CartVec &cv) const;
   /// Sets vector to unit length.
   void normalize() { *this /= length(); }
   /// Calculates inner product.
   double dot(const CartVec &v) const
   {
      return _x * v._x + _y * v._y + _z * v._z;
   }
   /// Calculates the angle [rad] between vector and v.
   double angle(const CartVec &v) const;
   /// Rotates around z.
   void rotateAroundZ(const double cosPhi, const double sinPhi);
   /// Rotates around y.
   void rotateAroundY(const double cosPhi, const double sinPhi);
   /// Rotates around x.
   void rotateAroundX(const double cosPhi, const double sinPhi);
   /// Rotates around an arbitrarily rotation axis.
   void rotateAround(const CartVec &axis, double cosPhi, double sinPhi);

private:
   double _x;
   double _y;
   double _z;
};

#endif // CARTVEC_H
