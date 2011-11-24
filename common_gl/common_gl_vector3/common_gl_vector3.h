#ifndef COMMON_GL_VECTOR3H
#define COMMON_GL_VECTOR3H

#include <GL/gl.h>

class CGLVector3
{
private:
GLdouble        m_vector[3];

public:
                CGLVector3();
                CGLVector3(const CGLVector3& vector);
                CGLVector3(const GLdouble* vector);
                CGLVector3(const GLdouble x, const GLdouble y, const GLdouble z);
                ~CGLVector3();

CGLVector3&     operator = (const CGLVector3& vector);
CGLVector3&     operator += (const CGLVector3& vector);
GLdouble        operator [] (int index) const;
GLdouble&       operator [] (int index);
                operator GLdouble* () const;

GLdouble        GetX() const;
GLdouble        GetY() const;
GLdouble        GetZ() const;
const GLdouble* GetVector() const;

void            SetX(GLdouble x);
void            SetY(GLdouble y);
void            SetZ(GLdouble z);
void            SetVector(const GLdouble* vector);
CGLVector3&     AddVector(const CGLVector3& vector);
};

#endif
