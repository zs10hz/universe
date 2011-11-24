#include <math.h>
#include <GL/glu.h>
#include "common_gl_camera.h"

CGLCamera::CGLCamera()
{
m_distance = 0.0;
m_oy = 0.0;
m_ox = 0.0;
m_oz = 0.0;
m_compilled = 0;
}

CGLCamera::CGLCamera(const CGLVector3& object, GLdouble distance, GLdouble oy, GLdouble ox, GLdouble oz): m_object( object )
{
m_distance = distance;
m_oy = oy;
m_ox = ox;
m_oz = oz;
m_compilled = 0;
}

CGLCamera::~CGLCamera()
{
Clear();
}

void CGLCamera::Clear()
{
if ( m_compilled != 0)
  glDeleteLists( m_compilled, 1 );

m_compilled = 0;
m_distance = 0.0;
m_oy = 0.0;
m_ox = 0.0;
m_oz = 0.0;
}

CGLVector3 CGLCamera::SetObject(const CGLVector3& object)
{
m_object = object;
return m_object;
}

CGLVector3 CGLCamera::MoveObject(const CGLVector3& vector)
{
m_object += vector;
return m_object;
}

GLdouble& CGLCamera::GetDistance()
{
return m_distance;
}

GLdouble CGLCamera::SetOX(const GLdouble& ox)
{
m_ox = ox;
return m_ox;
}

GLdouble CGLCamera::MoveOX(const GLdouble& delta)
{
m_ox += delta;
return m_ox;
}

GLdouble CGLCamera::SetOY(const GLdouble& oy)
{
m_oy = oy;
return m_oy;
}

GLdouble CGLCamera::MoveOY(const GLdouble& delta)
{
double sign = 1.0;
if ( cos( m_ox ) < 0 )
  sign = -1.0;

m_oy += sign * delta;
return m_oy;
}

GLdouble CGLCamera::SetOZ(const GLdouble& oz)
{
m_oz = oz;
return m_oz;
}

GLdouble CGLCamera::MoveOZ(const GLdouble& delta)
{
m_oz += delta;
return m_oz;
}

bool CGLCamera::Compile()
{
GLuint listid = glGenLists( 1 );
if ( listid == 0 )
  return false;

m_cam[0] = m_distance * cos( m_ox ) * sin( m_oy );
m_cam[1] = m_distance * sin( m_ox );
m_cam[2] = m_distance * cos( m_ox ) * cos( m_oy );

double sign = 1.0;
if ( cos( m_ox ) < 0 )
  sign = -1.0;

glNewList( listid, GL_COMPILE );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluLookAt( m_cam[0], m_cam[1], m_cam[2], m_object[0], m_object[1], m_object[2], sin(m_oz), sign*cos(m_oz), 0 );
glEndList();

if ( m_compilled != 0 )
  glDeleteLists( m_compilled, 1 );

m_compilled = listid;
return true;
}

void CGLCamera::Draw()
{
if ( m_compilled == 0 )
  {
  bool result = Compile();
  if ( result == false )
    return;
  }

glCallList( m_compilled );
}
