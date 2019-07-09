#ifndef BALL_H
#define BALL_H

#include "Drawable.h"
#include "XYZrZ.h"

class Ball : public Drawable
{
public:
   Ball(double R, const XYZrZ &xyzRz);
   Ball(const Ball &) = delete;
   Ball &operator=(const Ball &) = delete;
   ~Ball() override;

   void draw() const override;

private:
   double R_;
   XYZrZ XYZrZ_;
   GLUquadricObj *pBody_;
};

#endif // BALL_H
