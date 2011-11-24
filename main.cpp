#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

#include "common_gl_window.h"
#include "common_gl_fttext.h"
#include "common_gl_camera.h"

//Размеры окна на экране
GLint winWidth = 600;
GLint winHeight = 600;

GLint mx, my;

//Координаты отсекающего окна
GLdouble wxMin=-3, wyMin=-3, wxMax=3, wyMax=3;
//Плоскости отсечения
GLdouble dnear=10, dfar=1000*1000*1000;

GLuint OBJECTS_LIST = 0;

CGLFTFont myfont;
CGLFTText mytext( myfont );
CGLCamera mycamera( CGLVector3( 0.0, 0.0, 0.0 ), 300.0, 0.0, 0.0, 0.0 );

void init()
{
glClearColor( 0.0, 0.0, 0.0, 0.0 );
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
glFrustum( wxMin, wxMax, wyMin, wyMax, dnear, dfar );
}

void DisplayFunc()
{
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
mycamera.Draw();
//glDisable( GL_TEXTURE_2D );

GLfloat vector[] = { 0.0, 1.0, 0.0, 0.0 };
glLightfv( GL_LIGHT0, GL_POSITION, vector );


//glDisable(GL_TEXTURE_2D);
//glEnable( GL_BLEND );
//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

glColor4f( 0.0, 0.5, 0.0, 0.5 );
glCallList( OBJECTS_LIST );

//  glPushMatrix();
//  glTranslatef( -50000.0, -60.0, -20.0 );
//  glColor3f( 1.0, 0.0, 0.0 );
//  glutWireSphere( 40000.0, 100, 100 );
//  glPopMatrix();

glPushMatrix();
glTranslatef( 0.0, 20.0, 0.0 );
//glColor3f( 1.0, 0.0, 0.0 );
//glutWireSphere( 10.0, 10, 10 );
glutSolidSphere( 10.0, 30, 30 );
glTranslatef( 20.0, 20.0, 0.0 );
//glColor3f( 1.0, 1.0, 0.0 );
//glutWireSphere( 10.0, 10, 10 );
glutSolidSphere( 10.0, 30, 30 );
glTranslatef( -30.0, 20.0, 20.0 );
//glColor3f( 0.0, 0.0, 1.0 );
//glutWireSphere( 10.0, 10, 10 );
glutSolidSphere( 10.0, 30, 30 );
glPopMatrix();

//glEnable(GL_TEXTURE_2D);
//glMatrixMode( GL_MODELVIEW );
//glPushMatrix();
//glLoadIdentity();
//glMatrixMode( GL_PROJECTION );
//glPushMatrix();
//glLoadIdentity();
//gluOrtho2D( 0.0, 600, 0.0, 600 );
//mytext.Draw();
//glMatrixMode( GL_PROJECTION );
//glPopMatrix();
//glMatrixMode( GL_MODELVIEW );
//glPopMatrix();

glFinish();
glutSwapBuffers();
}

void ReshapeFunc(GLint newW, GLint newH)
{
glViewport( 0, 0, newW, newH );
winWidth = newW;
winHeight = newH;
}

void MouseFunc(GLint Button, GLint Action, GLint xMouse, GLint yMouse)
{
//Button == GLUT_RIGHT_BUTTON
if ( Action == GLUT_DOWN )
  {
  mx = xMouse;
  my = yMouse;
  }
}

void MouseWheelFunc(GLint wheel, GLint direction, GLint x, GLint y)
{
mycamera.GetDistance() += mycamera.GetDistance() * direction / 10;
mycamera.Compile();
glutPostRedisplay();
}

void MotionFunc(GLint x, GLint y)
{
GLdouble dx = mx - x;
GLdouble dy = y - my;
mx = x;
my = y;

mycamera.MoveOX( dy * M_PI/360 );
mycamera.MoveOY( dx * M_PI/360 );
mycamera.Compile();
glutPostRedisplay();
}

void CompileGrid(GLdouble x, GLdouble y, GLdouble z, GLuint xwidth, GLuint zwidht, GLuint xcount, GLint zcount)
{
GLdouble dx = xwidth / xcount;
GLdouble dz = zwidht / zcount;

if ( OBJECTS_LIST != 0 )
  glDeleteLists( OBJECTS_LIST, 1 );
OBJECTS_LIST = glGenLists( 1 );

glNewList( OBJECTS_LIST, GL_COMPILE );
  glBegin( GL_LINES );
    // x - lines
    for (int xi = 0; xi <= xcount; ++xi)
      {
      glVertex3f( x + dx * xi, y, z );
      glVertex3f( x + dx * xi, y, z + zwidht );
      }
    // z - lines
    for (int zi = 0; zi <= zcount; ++zi)
      {
      glVertex3f( x, y, z + dz * zi );
      glVertex3f( x + xwidth, y, z + dz * zi );
      }
  glEnd();
glEndList();
}

int main(int argc, char* argv[])
{
CGLWindow window1( "window1", 100, 50, 300, 600, GLW_DOUBLE | GLW_RGBA );
window1.CreateWindow();
IGLWindow* win = window1.CreateSubWindow( "my subwindow", 0, 0, 100, 100, GLW_DOUBLE | GLW_RGBA );
win->CreateWindow();
//delete ((CGLWindow*)win);
//window1.DestroyWindow();
//CGLWindow window2( "window2", 100, 50, 300, 600, GLW_DOUBLE | GLW_RGBA );
//window2.CreateWindow();

sleep( 1 );
window1.ShowWindow();

glutInit( &argc, argv );
glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
glutInitWindowPosition( 50, 50 );
glutInitWindowSize( winWidth, winHeight );
glutCreateWindow( "test3d" );
glEnableClientState( GL_VERTEX_ARRAY );
init();
CompileGrid( -500, 0, -500, 1000, 1000, 100, 100 );
mycamera.Draw();

//myfont.Make( "arial.ttf", 14, true );
//mytext.SetText( "test string" );
//mytext.Compile();

glutDisplayFunc( DisplayFunc );
glutReshapeFunc( ReshapeFunc );
glutMouseFunc( MouseFunc );
glutMouseWheelFunc( MouseWheelFunc );
glutMotionFunc( MotionFunc );
glEnable( GL_DEPTH_TEST );
glEnable( GL_CULL_FACE );
glCullFace( GL_BACK );
glEnable( GL_ALPHA_TEST );
glShadeModel( GL_SMOOTH );
glEnable( GL_NORMALIZE );
glEnable( GL_LIGHTING );
glEnable( GL_DITHER );
GLfloat Bcolor[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat Wcolor[] = { 1.0, 1.0, 1.0, 1.0 };
glLightfv( GL_LIGHT0, GL_AMBIENT, Bcolor );
glLightfv( GL_LIGHT0, GL_DIFFUSE, Wcolor );
glLightfv( GL_LIGHT0, GL_SPECULAR, Wcolor );

glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5 );
glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.75 );
glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.4 );
glEnable( GL_LIGHT0 );

glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR );
//GLfloat Dcoeff[] = { 0.2, 0.4, 0.9, 1.0 };
GLfloat Dcoeff[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat Scoeff[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat Semission[] = { 0.1, 0.0, 0.0, 1.0 };
glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Dcoeff );
glMaterialfv( GL_FRONT, GL_SPECULAR, Scoeff );
glMaterialfv( GL_FRONT, GL_EMISSION, Semission );
glMaterialf( GL_FRONT, GL_SHININESS, 25.0 );

glViewport( 0, 0, 600, 600 );
glutMainLoop();
while ( true )
  sleep( 1 );
}
