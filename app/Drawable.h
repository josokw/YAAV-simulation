#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <QGLWidget>

class Drawable
{
public:
   Drawable() = default;
   virtual ~Drawable() = default;

   virtual void draw() const = 0;
};

#endif // DRAWABLE_H
