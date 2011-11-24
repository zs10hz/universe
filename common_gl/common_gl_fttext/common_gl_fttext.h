#ifndef COMMON_GL_FTTEXTH
#define COMMON_GL_FTTEXTH

#include <string>
using namespace std;

#include "common_gl_ftfont.h"

class CGLFTText
{
private:
const CGLFTFont&  m_font;
string            m_text;
uint              m_width;
uint              m_count;
GLuint            m_compilled;
GLuint*           m_calllist;

public:
                  CGLFTText(const CGLFTFont& font);
                  CGLFTText(const CGLFTFont& font, string text);
                  ~CGLFTText();
void              Clear();

void              SetFont(const CGLFTFont& font);
void              SetText(string text);
string            GetText() const;
void              GenCallList();
bool              Compile();
void              Draw() const;

uint              GetWidth() const;
uint              GetHeight() const;
uint              GetDownShift() const;
};

#endif
