#include "common_gl_ftfont.h"

inline uint next_p2 (uint value)
{
uint result = 1;
while( result < value )
  result <<= 1;
return result;
}

CGLFTFont::CGLFTFont()
{
m_lists = 0;
m_height = 0;
m_downshift = 0;
m_symbolspacer = 0;
memset( m_widths, 0, sizeof(m_widths) );
}

CGLFTFont::~CGLFTFont()
{
Clear();
}

void CGLFTFont::Clear()
{
if ( m_textures == 0 )
  return;

if ( m_lists != 0 )
  glDeleteLists( m_lists, symbolcount );
m_lists = 0;

for (uint index = 0; index < symbolcount; ++index)
  m_textures[index].Clear();

m_height = 0;
m_downshift = 0;
m_symbolspacer = 0;
memset( m_widths, 0, sizeof(m_widths) );
}

bool CGLFTFont::Make(string filename, int height, bool blend)
{
Clear();
m_symbolspacer = height / 20 + 1;
m_height = height;

FT_Library library;
int error = FT_Init_FreeType( &library );
if ( error != 0 )
  return false;

FT_Face face;
error = FT_New_Face( library, filename.c_str(), 0, &face );
if ( error != 0 )
  return false;

int ftheight = height << 6;
FT_Set_Char_Size( face, ftheight, ftheight, 96, 96 );

m_lists = glGenLists( symbolcount );

m_downshift = 0;

for (uchar index = 0; index < symbolcount; ++index)
  {
  bool result = MakeSymbol( face, index, blend );
  if ( result == false )
    return false;
  }

FT_Done_Face(face);
FT_Done_FreeType(library);
}

bool CGLFTFont::MakeSymbol(FT_Face face, uint index, bool blend)
{
GLuint list = m_lists + index;
CGLTexture& texture = m_textures[index];
char Symbol = index + startsymbol;
if ( Symbol == ' ' )
  return MakeSpace( index );

uint CharIndex = FT_Get_Char_Index( face, Symbol );

int error = FT_Load_Glyph( face, CharIndex, FT_LOAD_DEFAULT );
if( error != 0 )
  return false;

FT_Glyph glyph;
error = FT_Get_Glyph( face->glyph, &glyph );
if( error != 0 )
  return false;

//!!******************************
FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
FT_Bitmap& bitmap = bitmap_glyph->bitmap;
//!!***********************
int& bit_width = bitmap.width;
int& bit_height = bitmap.rows;

m_widths[index] = bit_width;

int tex_width = next_p2( bit_width );
int tex_height = next_p2( bit_height );

// Выделим память для данных текстуры.
size_t size = 2 * tex_width * tex_height;
GLubyte* texture_data = new GLubyte[ size ];
memset( texture_data, 0, size );

for(int y = 0; y < bit_height; ++y)
  for(int x=0; x < bit_width; ++x)
    {
    if (blend == false)
      {
      texture_data[2 * ( x + y*tex_width )] = 0xFF;
      if ( bitmap.buffer[x + bit_width*y] < 0x80)
        texture_data[2 * (x + y*tex_width) + 1] = 0;
      else
        texture_data[2 *( x + y*tex_width) + 1] = 0xFF;
      }
    else
      {
      texture_data[ 2 * (x + y*tex_width) ] = 0xFF;
      texture_data[2 * (x + y*tex_width) + 1] = bitmap.buffer[x + bit_width*y];
      }
    }

texture.Load( tex_width, tex_height, GL_UNSIGNED_BYTE, texture_data, GL_RGBA, 0 ,0, GL_LUMINANCE_ALPHA );
texture.SetParametr( GL_TEXTURE_MAG_FILTER, GL_LINEAR );
texture.SetParametr( GL_TEXTURE_MIN_FILTER, GL_LINEAR );

delete []texture_data;

glNewList( list, GL_COMPILE );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  texture.Bind();

  double xscale = (double)bit_width / (double)tex_width;
  double yscale = (double)bit_height / (double)tex_height;

  glMatrixMode(GL_MODELVIEW);
  int downshift = 0 - (bitmap_glyph->top - bit_height);
  if ( downshift > 0 )
    {
    if ( m_downshift < downshift )
      m_downshift = downshift;

    glPushMatrix();
    glTranslatef(0,-downshift,0);
    }

  glBegin(GL_QUADS);
    glTexCoord2d(0,0);
    glVertex2f(0,bitmap.rows);

    glTexCoord2d(0,yscale);
    glVertex2f(0,0);

    glTexCoord2d(xscale,yscale);
    glVertex2f(bitmap.width,0);

    glTexCoord2d(xscale,0);
    glVertex2f(bitmap.width,bitmap.rows);
  glEnd();

  if ( downshift > 0 )
    glPopMatrix();

  glTranslatef( bit_width + m_symbolspacer, 0, 0 );

glEndList();
}

GLuint CGLFTFont::GetListId(char symbol) const
{
uint index = symbol - startsymbol;
if ( index > symbolcount)
  return 0;
return m_lists + index;
}

bool CGLFTFont::MakeSpace(uint index)
{
GLuint list = m_lists + index;
glNewList( list, GL_COMPILE );
  glTranslatef( GetHeght() / 2, 0, 0 );
glEndList();
return true;
}

GLuint CGLFTFont::GetHeght() const
{
return m_height;
}

GLuint CGLFTFont::GetWigth(char symbol) const
{
uint index = symbol - startsymbol;
return m_widths[index];
}

uint CGLFTFont::GetSymbolSpacer() const
{
return m_symbolspacer;
}

uint CGLFTFont::GetDownShift() const
{
return m_downshift;
}
