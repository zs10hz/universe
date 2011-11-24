#ifndef COMMON_GL_TEXTUREH
#define COMMON_GL_TEXTUREH

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
using namespace std;

class CGLTexture
{
private:
GLuint  m_textureid;

public:
        CGLTexture();
        CGLTexture(GLuint id);
        CGLTexture(const CGLTexture& r_value);
        ~CGLTexture();

GLuint  GetId();
void    SetId(GLuint id);

void    Clear();

bool    Load(GLint width, GLint height, GLuint type, const GLvoid* pixels, GLint internalformat = GL_RGB, GLint level = 0, GLint border = 0, GLuint format = 0, GLint target = GL_TEXTURE_2D);

bool    SetParametr(GLuint param, GLint value, GLuint target = GL_TEXTURE_2D);

bool    Bind(GLint target = GL_TEXTURE_2D);
};

#endif
