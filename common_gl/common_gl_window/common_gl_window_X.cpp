#include <assert.h>
#include "common_gl_window_X.h"

KEY_VK XKeyEventToKeyVK(XKeyEvent* xkey)
{
KEY_VK key;
KeySym keysym = XLookupKeysym( xkey, 0 );
switch ( keysym )
  {
  case XK_F1:
    key = KEY_VK_F1;
    break;
  case XK_F2:
    key = KEY_VK_F2;
    break;
  case XK_F3:
    key = KEY_VK_F3;
    break;
  case XK_F4:
    key = KEY_VK_F4;
    break;
  case XK_F5:
    key = KEY_VK_F5;
    break;
  case XK_F6:
    key = KEY_VK_F6;
    break;
  case XK_F7:
    key = KEY_VK_F7;
    break;
  case XK_F8:
    key = KEY_VK_F8;
    break;
  case XK_F9:
    key = KEY_VK_F9;
    break;
  case XK_F10:
    key = KEY_VK_F10;
    break;
  case XK_F11:
    key = KEY_VK_F11;
    break;
  case XK_F12:
    key = KEY_VK_F12;
    break;
  case XK_F13:
    key = KEY_VK_F13;
    break;
  case XK_F14:
    key = KEY_VK_F14;
    break;
  case XK_F15:
    key = KEY_VK_F15;
    break;
  case XK_F16:
    key = KEY_VK_F16;
    break;
  case XK_F17:
    key = KEY_VK_F17;
    break;
  case XK_F18:
    key = KEY_VK_F18;
    break;
  case XK_F19:
    key = KEY_VK_F19;
    break;
  case XK_F20:
    key = KEY_VK_F20;
    break;
  case XK_F21:
    key = KEY_VK_F21;
    break;
  case XK_F22:
    key = KEY_VK_F22;
    break;
  case XK_F23:
    key = KEY_VK_F23;
    break;
  case XK_F24:
    key = KEY_VK_F24;
    break;
  case XK_Escape:
    key = KEY_VK_ESCAPE;
    break;
  case XK_Return:
    key = KEY_VK_RETURN;
    break;
  default:
    {
    char* symbol = XKeysymToString( keysym );
    key = (KEY_VK)(*symbol);
    }
    break;
  }
return key;
}

MB XButtonToMB(int button)
{
return (MB)button;
}

CGLWindow_X::CGLWindow_X(string title, GLuint xpos, GLuint ypos, GLuint height, GLuint width, GLWOPT opt)
{
m_parent = 0;
m_created = false;
m_title = title;
m_xpos = xpos;
m_ypos = ypos;
m_height = height;
m_width = width;
m_opt = opt;
}

CGLWindow_X::CGLWindow_X(Window parent, string title, GLuint xpos, GLuint ypos, GLuint height, GLuint width, GLWOPT opt)
{
m_parent = parent;
m_created = false;
m_title = title;
m_xpos = xpos;
m_ypos = ypos;
m_height = height;
m_width = width;
m_opt = opt;
}

CGLWindow_X::~CGLWindow_X()
{
CGLWindow_X::DestroyWindow();
}

bool CGLWindow_X::CreateWindow()
{
if ( m_created == true )
  return false;

m_display = XOpenDisplay( NULL );
if ( m_display == 0 )
  return false;

bool glx_support = glXQueryExtension( m_display, NULL, NULL );
if ( glx_support == false )
  return false;

m_screen = DefaultScreen( m_display );

int attr[] = { GLX_RGBA, GLX_DOUBLEBUFFER, 0 };
m_attr = attr;

m_visualinfo = glXChooseVisual( m_display, m_screen, m_attr );
if ( m_visualinfo == NULL )
  return false;

m_winattr.border_pixel = 0;
m_winattr.background_pixel = 0;
int rootwindow = RootWindow( m_display, m_screen );
int cmColorMap = XCreateColormap( m_display, rootwindow, m_visualinfo->visual, AllocNone );
m_winattr.colormap = cmColorMap;
m_winattr.event_mask = ExposureMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | ButtonMotionMask | SubstructureNotifyMask;

if ( m_parent == 0 )
  m_parent = rootwindow;

m_window  = XCreateWindow( m_display, m_parent, m_xpos, m_ypos, m_width, m_height,
 1, m_visualinfo->depth, InputOutput, m_visualinfo->visual,
CWBorderPixel | CWColormap | CWEventMask, // Типы атрибутов окна
&m_winattr );

m_context = glXCreateContext( m_display, m_visualinfo, NULL, true );
XFree( m_visualinfo );
if ( m_context == NULL )
  return false;

SetTitle( m_title );
Create();
}

IGLWindow* CGLWindow_X::CreateSubWindow(string title, GLuint xpos, GLuint ypos, GLuint height, GLuint width, GLWOPT opt)
{
return new CGLWindow_X( title, xpos, ypos, height, width, opt );
}

void CGLWindow_X::DestroyWindow()
{
if ( m_created == false )
  return;

XDestroyWindow( m_display, m_window );//!!
WaitForTerminate();
m_created = false;
}

void CGLWindow_X::DestroyWindowFunc()
{
}

void CGLWindow_X::Execute()
{
m_created = true;
Select();
ReshapeFunc( m_width, m_height );
XMapWindow( m_display, m_window );
XEvent event;
while ( true )
  {
  XNextEvent( m_display, &event );
  LockForTerminate();
  switch ( event.type )
    {
    case Expose:
      DisplayFunc();
      break;
    case ConfigureNotify:
      ReshapeFunc( event.xconfigure.width, event.xconfigure.height );
      break;
    case KeyPress:
      {
      KEY_VK key = XKeyEventToKeyVK( &(event.xkey) );
      KeyboardFunc( KEYDIRECT_DOWN, KEY_MOD_NONE, key );
      }
      break;
    case KeyRelease:
      {
      KEY_VK key = XKeyEventToKeyVK( &(event.xkey) );
      KeyboardFunc( KEYDIRECT_UP, KEY_MOD_NONE, key );
      }
      break;
    case ButtonPress:
      {
      int x = event.xbutton.x;
      int y = event.xbutton.y;
      MB button = XButtonToMB( event.xbutton.button );
      MouseButtonFunc( MB_DOWN, x, y, button );
      }
      break;
    case ButtonRelease:
      {
      int x = event.xbutton.x;
      int y = event.xbutton.y;
      MB button = XButtonToMB( event.xbutton.button );
      MouseButtonFunc( MB_DOWN, x, y, button );
      }
      break;
    case MotionNotify:
      {
      int x = event.xmotion.x;
      int y = event.xmotion.y;
      MouseMotionFunc( x, y );
      }
      break;
    case CreateNotify:
//            XCreateWindowEvent xcreatewindow;
      break;
    case DestroyNotify:
      DestroyWindowFunc();
      return;
    default:
      break;
    };
  UnLockForTerminate();
  };
}

void CGLWindow_X::DisplayFunc()
{
glClear( GL_COLOR_BUFFER_BIT );
SwapBuffers();
}

void CGLWindow_X::ReshapeFunc(GLuint width, GLuint height)
{
m_width = width;
m_height = height;

glViewport( 0, 0, m_width, m_height );
}

void CGLWindow_X::KeyboardFunc(KEY_DIRECT direction, KEY_MOD modificators, KEY_VK key)
{
}

void CGLWindow_X::MouseButtonFunc(MB_DIRECT direction, int x, int y, MB button)
{
}

void CGLWindow_X::MouseMotionFunc(int x, int y)
{
}

void CGLWindow_X::SwapBuffers()
{
glXSwapBuffers( m_display, m_window );
}

void CGLWindow_X::SetTitle()
{
XSetStandardProperties( m_display, m_window, m_title.c_str(), m_title.c_str(), 0, NULL, 0, NULL );
}

void CGLWindow_X::SetTitle(string title)
{
m_title = title;
SetTitle();
}

bool CGLWindow_X::Select()
{
return glXMakeCurrent( m_display, m_window, m_context );
}

void CGLWindow_X::ShowWindow()
{
XMapWindow( m_display, m_window );
}

void CGLWindow_X::HideWindow()
{
XUnmapWindow( m_display, m_window );
}
