#ifndef POINT_H
#define POINT_H

class CartVec;

/// Represents a point in 3D.
class Point
{
   /// cv = p1 - p2
   friend CartVec operator-(const Point &lhs, const Point &rhs);
   /// p = p1 + cv
   friend Point operator+(const Point &lhs, const CartVec &rhs);
   /// p = p1 - cv
   friend Point operator-(const Point &lhs, const CartVec &rhs);

public:
   Point() = default;
   Point(double x, double y, double z);

   double get_x() const { return x_; };
   double get_y() const { return y_; };
   double get_z() const { return z_; };
   void set_x(double x) { x_ = x; };
   void set_y(double y) { y_ = y; }
   void set_z(double z) { z_ = z; }

   Point &operator+=(const CartVec &rhs);
   Point &operator-=(const CartVec &rhs);

private:
   double x_ = 0.0;
   double y_ = 0.0;
   double z_ = 0.0;
};

#endif // POINT_H
