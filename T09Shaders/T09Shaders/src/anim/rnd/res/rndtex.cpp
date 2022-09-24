#include "rndres.h"

int resources::AddImg( const char *Name, int W, int H, int C, BYTE *Bits)
{
  int mips;

  if (NumOfTextures >= MAX_TEXTURES)
    return -1;

  // Allocate texture space
  glGenTextures(1, &(tex[NumOfTextures].TexId));
  glBindTexture(GL_TEXTURE_2D, tex[NumOfTextures].TexId);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  mips = log(W > H ? W : H) / log(2);
  mips = mips < 1 ? 1 : mips;

  glTexStorage2D(GL_TEXTURE_2D, mips,
    C == 4 ? GL_RGBA8 : C == 3 ? GL_RGB8 : GL_R8, W, H);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H,
    C == 4 ? GL_BGRA : C == 3 ? GL_BGR : GL_LUMINANCE, GL_UNSIGNED_BYTE, Bits);

  glGenerateMipmap(GL_TEXTURE_2D);


  // Upload texture
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, 0);

  // Add to stock
  strncpy(tex[NumOfTextures].Name, Name, STR_MAX - 1);
  tex[NumOfTextures].W = W;
  tex[NumOfTextures].H = H;

  glBindTexture(GL_TEXTURE_2D, 0);
  return NumOfTextures++;
}
