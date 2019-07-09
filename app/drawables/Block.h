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
   Block(double l, double w, double h, const XYZrZ &xyzRz);
   virtual ~Block() override = default;

   const math::Polygon &getCollisionShape() const { return _corners; }
   virtual void draw() const override;

private:
   double _l;
   double _h;
   double _w;
   XYZrZ _XYZrZ;
   math::Polygon _corners;
};

#endif // BLOCK_H
