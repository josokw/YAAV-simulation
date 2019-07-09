#ifndef BLOCK_H
#define BLOCK_H

#include "Drawable.h"
#include "Polygon.h"
#include "XYZrZ.h"

/// A Block has length, width and height.
/// Can be used to model a chair.
class Block : public Drawable
{
public:
   Block(double length, double width, double height, const XYZrZ &xyzRz);
   ~Block() override = default;

   void draw() const override;
   const math::Polygon &getCollisionShape() const { return corners_; }

private:
   double length_;
   double height_;
   double width_;
   XYZrZ XYZrZ_;
   math::Polygon corners_;
};

#endif // BLOCK_H
