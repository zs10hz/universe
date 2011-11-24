#ifndef COMMON_GL_CAMERAH
#define COMMON_GL_CAMERAH

#include "common_gl_vector3.h"

class CGLCamera
{
private:
CGLVector3  m_cam;
CGLVector3  m_object;
GLdouble    m_distance;
GLdouble    m_oy;
GLdouble    m_ox;
GLdouble    m_oz;
GLuint      m_compilled;

public:
            CGLCamera();
            CGLCamera(const CGLVector3& object, GLdouble distance, GLdouble oy, GLdouble ox, GLdouble oz);
            ~CGLCamera();
void        Clear();

CGLVector3 SetObject(const CGLVector3& object);
CGLVector3 MoveObject(const CGLVector3& vector);

//GLdouble   SetDistance(const GLdouble& distance);
//GLdouble   MoveDistance(const GLdouble& delta);
GLdouble&  GetDistance();

GLdouble   SetOX(const GLdouble& ox);
GLdouble   MoveOX(const GLdouble& delta);

GLdouble   SetOY(const GLdouble& oy);
GLdouble   MoveOY(const GLdouble& delta);

GLdouble   SetOZ(const GLdouble& oz);
GLdouble   MoveOZ(const GLdouble& delta);

bool       Compile();
void       Draw();
};

#endif
