#include "rndres.h"

int resources::AddImg( char *Name, int W, int H, DWORD *Bits)
{
  if (NumOfTextures >= MAX_TEXTURES)
    return -1;

  // Allocate texture space
  glGenTextures(1, &(tex[NumOfTextures]->TexId));
  glBindTexture(GL_TEXTURE_2D, tex[NumOfTextures]->TexId);

  // Upload texture
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  strncpy(tex[NumOfTextures]->Name, Name, STR_MAX - 1);
  tex[NumOfTextures]->W = W;
  tex[NumOfTextures]->H = H;

  glBindTexture(GL_TEXTURE_2D, 0);
  return NumOfTextures++;
}
