#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/gl.h>
#include <GL/glut.h>

/// Abstract base class for drawables.
class Drawable
{
public:
   Drawable() = default;
   Drawable(const Drawable &other) = default;
   Drawable& operator=(const Drawable &other) = default;
   Drawable(Drawable &&other) = default;
   Drawable& operator=(Drawable &&other) = default;
   virtual ~Drawable() = default;

   virtual void draw() const = 0;
};

#endif // DRAWABLE_H
