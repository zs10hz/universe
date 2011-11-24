#ifndef COMMOM_GL_WINDOWH
#define COMMOM_GL_WINDOWH

#ifdef WIN32
  #include "common_gl_window_W.h"
  typedef CGLWindow_W CGLWindow;
#else
  #include "common_gl_window_X.h"
  typedef CGLWindow_X CGLWindow;
#endif

#endif
