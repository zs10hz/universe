#ifndef COMMON_GL_WINDOW_XH
#define COMMON_GL_WINDOW_XH

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include "common_gl_window.i"
#include "common_thread.h"

class CGLWindow_X:
  public IGLWindow,
  protected CThread
{
private:
bool                  m_created;
Display*              m_display;
int                   m_screen;
int*                  m_attr;
XVisualInfo*          m_visualinfo;
Window                m_parent;
Window                m_window;
GLXContext            m_context;
XSetWindowAttributes  m_winattr;

                      CGLWindow_X(Window parent, string title, GLuint xpos, GLuint ypos, GLuint height, GLuint width, GLWOPT opt);
protected:
void                  Execute();

void                  DisplayFunc();
void                  ReshapeFunc(GLuint width, GLuint height);

void                  MouseButtonFunc(MB_DIRECT direction, int x, int y, MB button);
void                  MouseMotionFunc(int x, int y);

void                  KeyboardFunc(KEY_DIRECT direction, KEY_MOD modificators, KEY_VK key);

void                  SetTitle();

void                  DestroyWindowFunc();

public:
                      CGLWindow_X(string title, GLuint xpos, GLuint ypos, GLuint width, GLuint height, GLWOPT opt);
                      ~CGLWindow_X();

IGLWindow*            CreateSubWindow(string title, GLuint xpos, GLuint ypos, GLuint width, GLuint height, GLWOPT opt);

bool                  CreateWindow();
void                  DestroyWindow();

void                  SwapBuffers();

void                  SetTitle(string title);
bool                  Select();

void                  ShowWindow();
void                  HideWindow();
};

#endif
