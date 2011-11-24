#ifndef COMMON_GL_WINDOWI
#define COMMON_GL_WINDOWI

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
using namespace std;

typedef unsigned int uint;
typedef uint GLWOPT;

enum
{
GLW_SINGLE = 0x1,
GLW_DOUBLE = 0x2,
GLW_RGB = 0x4,
GLW_RGBA = 0x8,
GLW_DEPTH = 0x10
};

enum KEY_DIRECT
{
KEYDIRECT_DOWN,
KEYDIRECT_UP
};

enum KEY_MOD
{
KEY_MOD_NONE    = 0,
KEY_MOD_SHIFT   = 0x01,
KEY_MOD_CTRL    = 0x02,
KEY_MOD_ALT     = 0x04,
KEY_MOD_WINDOW  = 0x08
};

enum KEY_VK
{
KEY_VK_F1 = 255,
KEY_VK_F2,
KEY_VK_F3,
KEY_VK_F4,
KEY_VK_F5,
KEY_VK_F6,
KEY_VK_F7,
KEY_VK_F8,
KEY_VK_F9,
KEY_VK_F10,
KEY_VK_F11,
KEY_VK_F12,
KEY_VK_F13,
KEY_VK_F14,
KEY_VK_F15,
KEY_VK_F16,
KEY_VK_F17,
KEY_VK_F18,
KEY_VK_F19,
KEY_VK_F20,
KEY_VK_F21,
KEY_VK_F22,
KEY_VK_F23,
KEY_VK_F24,
KEY_VK_RETURN,
KEY_VK_ESCAPE
};

enum MB_DIRECT
{
MB_DOWN,
BM_UP
};

enum MB
{
MB_BUTTON1 = 1,
MB_LEFT = MB_BUTTON1,
MB_BUTTON2,
MB_RIGHT = MB_BUTTON2,
MB_BUTTON3,
MB_MIDDLE = MB_BUTTON3,
MB_BUTTON4,
MB_WHEEL_DONW = MB_BUTTON4,
MB_BUTTON5,
MB_WHEEL_UP = MB_BUTTON5,
MB_BUTTON6,
MB_BUTTON7,
MB_BUTTON8
};

class IGLWindow
{
protected:
GLWOPT              m_opt;
string              m_title;
GLuint              m_xpos;
GLuint              m_ypos;
GLuint              m_height;
GLuint              m_width;

protected:
virtual void        DisplayFunc() = 0;
virtual void        ReshapeFunc(GLuint width, GLuint height) = 0;

virtual void        MouseButtonFunc(MB_DIRECT direction, int x, int y, MB button) = 0;
virtual void        MouseMotionFunc(int x, int y) = 0;

virtual void        KeyboardFunc(KEY_DIRECT direction, KEY_MOD modificators, KEY_VK key) = 0;

virtual void        SetTitle() = 0;

public:
/*
virtual              IGLWindow(string title, GLuint xpos, GLuint ypos, GLuint width, GLuint height, GLWOPT opt) = 0;
*/
virtual IGLWindow*  CreateSubWindow(string title, GLuint xpos, GLuint ypos, GLuint width, GLuint height, GLWOPT opt) = 0;

virtual bool        CreateWindow() = 0;
virtual void        DestroyWindow() = 0;

virtual void        SwapBuffers() = 0;

virtual void        ShowWindow() = 0;
virtual void        HideWindow() = 0;

virtual void        SetTitle(string title) = 0;
virtual bool        Select() = 0;
};

#endif
