#include <stdio.h>
#include "common_gl_bmptexture.h"

typedef unsigned long ulong;

typedef long LONG;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;

//File information header
//provides general information about the file
typedef struct tagBITMAPFILEHEADER { 
  WORD    bfType; 
  DWORD   bfSize; 
  WORD    bfReserved1; 
  WORD    bfReserved2; 
  DWORD   bfOffBits; 
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

//Bitmap information header
//provides information specific to the image data
typedef struct tagBITMAPINFOHEADER{
  DWORD  biSize; 
  LONG   biWidth; 
  LONG   biHeight; 
  WORD   biPlanes; 
  WORD   biBitCount; 
  DWORD  biCompression; 
  DWORD  biSizeImage; 
  LONG   biXPelsPerMeter; 
  LONG   biYPelsPerMeter; 
  DWORD  biClrUsed; 
  DWORD  biClrImportant; 
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

//Colour palette
typedef struct tagRGBQUAD {
  BYTE    rgbBlue; 
  BYTE    rgbGreen; 
  BYTE    rgbRed; 
  BYTE    rgbReserved; 
} RGBQUAD;

CBMPTexture::CBMPTexture()
{
glGenTextures( 1, &m_textureid );
}

CBMPTexture::~CBMPTexture()
{
glDeleteTextures( 1, &m_textureid );
}

bool CBMPTexture::Load(string filename)
{
BITMAPFILEHEADER header;
BITMAPINFOHEADER InfoHeader;

FILE* file = fopen( filename.c_str(), "rb" );
if ( file == 0 )
  return false;

fseek( file, 0, SEEK_SET );
fread( &header, sizeof(BITMAPFILEHEADER), 1, file );

const uint BITMAP_ID = 19778;
if( header.bfType != BITMAP_ID )
  {
  fclose( file );
  return false;
  }

fread( &InfoHeader, sizeof(BITMAPINFOHEADER), 1, file );

m_width = InfoHeader.biWidth;
m_height = InfoHeader.biHeight;

size_t size = (InfoHeader.biSizeImage == 0)? m_width * m_height * 3 : InfoHeader.biSizeImage;

fseek( file, header.bfOffBits, SEEK_SET );

char* data = new char[size];
if( data == NULL )
  {
  fclose( file );
  return false;
  }

fread( data, 1, size, file );
//memset( data, 0x88, size );

 // Bitmaps are saved in BGR format so we will make the image RGB by...
for(int index = 0; index < (int)size; index+=3)
  {
  int textureColors = data[index];
  data[index] = data[index + 2];
  data[index + 2] = textureColors;
  }

GLuint type = GL_RGB;
glBindTexture( GL_TEXTURE_2D, m_textureid );
glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST/*GL_LINEAR*/ );
glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST );
glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
gluBuild2DMipmaps( GL_TEXTURE_2D, type, m_width, m_height, type, GL_UNSIGNED_BYTE, data );
//glTexImage2D( GL_TEXTURE_2D, 0, type, m_width, m_height, 0, type, GL_UNSIGNED_BYTE, data) ;

delete []data;
}

void CBMPTexture::Bind()
{
glBindTexture( GL_TEXTURE_2D, m_textureid );
}
