#ifndef CFREETYPEFONTH
#define CFREETYPEFONTH

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <GL/glut.h>
#include <string>
using namespace std;

#include "common_gl_texture.h"

typedef unsigned char uchar;
typedef unsigned int uint;

const char startsymbol = ' ';
const char endsymbol = 'z';
const uint symbolcount = endsymbol - startsymbol + 1;

class CGLFTFont
{
private:
uint        m_symbolspacer;
uint        m_downshift;
GLuint      m_lists;
CGLTexture  m_textures[symbolcount];
GLuint      m_height;
GLuint      m_widths[symbolcount];

bool        MakeSpace(uint index);
bool        MakeSymbol(FT_Face face, uint index, bool blend);

public:
            CGLFTFont();
            ~CGLFTFont();
void        Clear();

GLuint      GetHeght() const;
GLuint      GetWigth(char symbol) const;

bool        Make(string filename, int height, bool blend);
GLuint      GetListId(char symbol) const;

uint        GetSymbolSpacer() const;
uint        GetDownShift() const;
};

#endif
