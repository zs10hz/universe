#ifndef CBMPTEXTUREH
#define CBMPTEXTUREH

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
using namespace std;

class CBMPTexture
{
private:
GLuint  m_textureid;
GLuint  m_height;
GLuint  m_width;

public:
        CBMPTexture();
        ~CBMPTexture();

bool    Load(string filename);
void    Bind();
};

#endif
