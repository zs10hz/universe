#include <assert.h>
#include "common_gl_vector3.h"

CGLVector3::CGLVector3()
{
m_vector[0] = 0.0;
m_vector[1] = 0.0;
m_vector[2] = 0.0;
}

CGLVector3::CGLVector3(const CGLVector3& vector)
{
m_vector[0] = vector.m_vector[0];
m_vector[1] = vector.m_vector[1];
m_vector[2] = vector.m_vector[2];
}

CGLVector3::CGLVector3(const GLdouble* vector)
{
m_vector[0] = vector[0];
m_vector[1] = vector[1];
m_vector[2] = vector[2];
}

CGLVector3::CGLVector3(const GLdouble x, const GLdouble y, const GLdouble z)
{
m_vector[0] = x;
m_vector[1] = y;
m_vector[2] = z;
}

CGLVector3::~CGLVector3()
{
}

CGLVector3& CGLVector3::operator = (const CGLVector3& vector)
{
SetVector( vector );
return *this;
}

CGLVector3& CGLVector3::operator += (const CGLVector3& vector)
{
return AddVector( vector );
}

GLdouble CGLVector3::operator [] (int index) const
{
assert( index < 3 && index >= 0 );
return m_vector[index];
}

GLdouble& CGLVector3::operator [] (int index)
{
assert( index < 3 && index >= 0 );
return m_vector[index];
}

CGLVector3::operator GLdouble*() const
{
return (GLdouble*)m_vector;
}

GLdouble CGLVector3::GetX() const
{
return m_vector[0];
}

GLdouble CGLVector3::GetY() const
{
return m_vector[1];
}

GLdouble CGLVector3::GetZ() const
{
return m_vector[2];
}

const GLdouble* CGLVector3::GetVector() const
{
return m_vector;
}

void CGLVector3::SetX(GLdouble x)
{
m_vector[0] = x;
}

void CGLVector3::SetY(GLdouble y)
{
m_vector[1] = y;
}

void CGLVector3::SetZ(GLdouble z)
{
m_vector[2] = z;
}

void CGLVector3::SetVector(const GLdouble* vector)
{
m_vector[0] = vector[0];
m_vector[1] = vector[1];
m_vector[2] = vector[2];
}

CGLVector3& CGLVector3::AddVector(const CGLVector3& vector)
{
m_vector[0] += vector.m_vector[0];
m_vector[1] += vector.m_vector[1];
m_vector[2] += vector.m_vector[2];
return *this;
}
