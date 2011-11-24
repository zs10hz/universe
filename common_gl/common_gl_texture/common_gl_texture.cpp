#include "common_gl_texture.h"

CGLTexture::CGLTexture()
{
m_textureid = 0;
}

CGLTexture::CGLTexture(GLuint id)
{
m_textureid = id;
}

CGLTexture::CGLTexture(const CGLTexture& r_value)
{
m_textureid = r_value.m_textureid;
}

CGLTexture::~CGLTexture()
{
Clear();
}

GLuint CGLTexture::GetId()
{
if ( m_textureid == 0 )
  glGenTextures( 1, &m_textureid );

return m_textureid;
}

void CGLTexture::SetId(GLuint id)
{
Clear();
m_textureid = id;
}

void CGLTexture::Clear()
{
if ( m_textureid != 0 )
  glDeleteTextures( 1, &m_textureid );
m_textureid = 0;
}

bool CGLTexture::Load(GLint width, GLint height, GLuint type, const GLvoid* pixels, GLint internalformat, GLint level, GLint border, GLuint format, GLint target)
{
Bind( target );
glTexImage2D( target, level, internalformat, width, height, border, format, type, pixels );
return true; //!TODO
}

bool CGLTexture::SetParametr(GLuint param, GLint value, GLuint target)
{
Bind();
glTexParameteri( target, param, value );
return true; //!TODO
}

bool CGLTexture::Bind(GLint target)
{
glBindTexture( target, GetId() );
return true; //!TODO
}
