#ifndef CARTVEC_H
#define CARTVEC_H

#include <cmath>
#include <iosfwd>

/// Class 'CartVec' represents a Cartesian vector [x,y,z] in 3D space.
/// @short Cartesian vector in 3D space.
class CartVec
{
   /// Testing for equality.
   /// \see CartVec::eps
   friend bool operator==(const CartVec &lhs, const CartVec &rhs);
   friend bool operator!=(const CartVec &lhs, const CartVec &rhs);
   /// Add 2 CartVec's.
   friend CartVec operator+(const CartVec &lhs, const CartVec &rhs);
   /// Subtract 2 CartVec's.
   friend CartVec operator-(const CartVec &lhs, const CartVec &rhs);
   /// Multiplication by a scalar (lhs).
   friend CartVec operator*(double lhs, const CartVec &rhs);
   /// Multiplication by a scalar (rhs).
   friend CartVec operator*(const CartVec &lhs, double rhs);
   /// Division by a scalar (rhs).
   friend CartVec operator/(const CartVec &lhs, double rhs);
   /// Output format: [x,y,z]
   friend std::ostream &operator<<(std::ostream &os, const CartVec &rhs);
   /// Input format: [x,y,z]  extra whitespaces allowed
   friend std::istream &operator>>(std::istream &is, CartVec &rhs);

public:
   static double eps;
   static const CartVec ZERO;
   static const CartVec UNIT_X;
   static const CartVec UNIT_Y;
   static const CartVec UNIT_Z;

   CartVec() = default;
   CartVec(double x_, double y_, double z_);
   CartVec(const CartVec &other) = default;
   CartVec &operator=(const CartVec &other) = default;
   CartVec(CartVec &&other) = default;
   CartVec &operator=(CartVec &&other) = default;
   ~CartVec() = default;

   double get_x() const { return x_; }
   double get_y() const { return y_; }
   double get_z() const { return z_; }
   void set_x(double x) { x_ = x; }
   void set_y(double y) { y_ = y; }
   void set_z(double z) { z_ = z; }

   /// Unary + operator
   CartVec operator+() const { return *this; }
   /// Unary - operator
   CartVec operator-() const { return {-x_, -y_, -z_}; }
   /// Compound assignment operator [x,y,z] += [a,b,c]
   CartVec &operator+=(const CartVec &rhs)
   {
      x_ += rhs.x_;
      y_ += rhs.y_;
      z_ += rhs.z_;
      return *this;
   }
   /// [x,y,z] -= [a,b,c]
   CartVec &operator-=(const CartVec &rhs)
   {
      x_ -= rhs.x_;
      y_ -= rhs.y_;
      z_ -= rhs.z_;
      return *this;
   }
   /// [x,y,z] *= s
   CartVec &operator*=(double rhs)
   {
      x_ *= rhs;
      y_ *= rhs;
      z_ *= rhs;
      return *this;
   }
   /// [x,y,z] /= s
   CartVec &operator/=(double rhs)
   {
      x_ /= rhs;
      y_ /= rhs;
      z_ /= rhs;
      return *this;
   }

   /// Calculates length: ||vector||
   double length() const { return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_); }
   /// Distance to other end point of a CartVec.
   double distance(const CartVec &cv) const;
   /// Sets vector to unit length.
   void normalize() { *this /= length(); }
   /// Calculates inner product.
   double dot(const CartVec &v) const
   {
      return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
   }
   /// Calulates cross product.
   CartVec cross(const CartVec &v) const
   {
      return {y_ * v.z_ - z_ * v.y_, -x_ * v.z_ + z_ * v.x_,
              x_ * v.y_ - y_ * v.x_};
   }
   /// Calculates the angle [rad] between vector and v.
   double angle(const CartVec &v) const;
   /// Rotates around z.
   void rotateAroundZ(double cosPhi, double sinPhi);
   /// Rotates around y.
   void rotateAroundY(double cosPhi, double sinPhi);
   /// Rotates around x.
   void rotateAroundX(double cosPhi, double sinPhi);
   /// Rotates around an arbitrarily rotation axis.
   void rotateAround(const CartVec &axis, double cosPhi, double sinPhi);

private:
   double x_{0.0};
   double y_{0.0};
   double z_{0.0};
};

#endif // CARTVEC_H
