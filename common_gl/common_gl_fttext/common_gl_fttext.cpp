#include "common_gl_fttext.h"

CGLFTText::CGLFTText(const CGLFTFont& font):
  m_font( font )
{
m_width = 0;
m_calllist = 0;
m_compilled = 0;
}

CGLFTText::CGLFTText(const CGLFTFont& font, string text):
  m_font( font )
{
m_width = 0;
m_calllist = 0;
m_compilled = 0;
SetText( text );
}

CGLFTText::~CGLFTText()
{
Clear();
}

void CGLFTText::Clear()
{
if ( m_calllist == NULL )
  return;

delete []m_calllist;
m_calllist = 0;

if ( m_compilled != 0 )
  glDeleteLists( m_compilled, 0 );
m_compilled = 0;
m_count = 0;
m_text = "";
}

void CGLFTText::SetText(string text)
{
Clear();
m_text = text;
m_count = text.size();
GenCallList();
}

void CGLFTText::GenCallList()
{
m_width = 0;

if ( m_calllist != 0 )
  delete []m_calllist;

m_calllist = new GLuint [ m_count ];

for (uint pos = 0; pos < m_count; ++pos)
  {
  char symbol = m_text[pos];
  m_calllist[pos] = m_font.GetListId( symbol );
  m_width += m_font.GetWigth( symbol ) + m_font.GetSymbolSpacer();
  }
}

string CGLFTText::GetText() const
{
return m_text;
}

void CGLFTText::SetFont(const CGLFTFont& font)
{
(CGLFTFont&)m_font = font;
GenCallList();
if ( m_compilled != 0 )
  Compile();
}

bool CGLFTText::Compile()
{
if ( m_compilled != 0 )
  glDeleteLists( m_compilled, 1 );

m_compilled = glGenLists( 1 );
if ( m_compilled == 0 )
  return 0;

glNewList( m_compilled, GL_COMPILE );
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glCallLists( m_count, GL_UNSIGNED_INT, m_calllist );
  glPopMatrix();
glEndList();
}

void CGLFTText::Draw() const
{
if ( m_compilled != 0 )
  glCallList( m_compilled );
else
  {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glCallLists( m_count, GL_UNSIGNED_INT, m_calllist );
  glPopMatrix();
  }
}

uint CGLFTText::GetWidth() const
{
return m_width;
}

uint CGLFTText::GetHeight() const
{
return m_font.GetHeght();
}

uint CGLFTText::GetDownShift() const
{
return m_font.GetDownShift();
}
