#include "rndres.h"

int resources::AddImg( std::string Name, int W, int H, int C, BYTE *Bits)
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
  //strncpy(tex[NumOfTextures].Name, Name, STR_MAX - 1);
  tex[NumOfTextures].Name = Name;
  tex[NumOfTextures].W = W;
  tex[NumOfTextures].H = H;

  glBindTexture(GL_TEXTURE_2D, 0);
  return NumOfTextures++;
}


void resources::AddTexture( material *Mtl, std::string TexName, const char *TexFile )
{
  HBITMAP hBm;  
  static int TexNo = -1;

  TexNo = FindTexture(TexName); 

  if (TexNo == -1)
  {
    hBm = (HBITMAP)LoadImage(NULL, TexFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (hBm != NULL)
    {
      BITMAP bm;
      GetObject(hBm, sizeof(bm), &bm);


      BYTE *mem = (BYTE *)bm.bmBits;
      TexNo = AddImg(TexName, bm.bmWidth, bm.bmHeight, 3, mem);
      DeleteObject(hBm);
    }
  }
  
  Mtl->Tex[0] = TexNo; 
}


int resources::AddTextureFromFile( material *Mtl, std::string TexName, const char *FileName)
{
  int res = -1;
  HBITMAP hBm;  

  res = FindTexture(TexName); 
  if (res == -1)
  {
    //Load texture
    hBm = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if(hBm != NULL)
    { 
      // Load texture from BMP
      BITMAP bm;
      GetObject(hBm, sizeof(bm), &bm);
      res = AddImg(TexName, bm.bmWidth, bm.bmHeight, bm.bmBitsPixel / 8, (BYTE *)bm.bmBits);

      DeleteObject(hBm);
    }
    else
    {
      // Load texture from G24/G32
      FILE *F;

      if ((F = fopen(FileName, "rb")) != NULL)
      {
        int W = 0, H = 0, flen, C = 0;
        BYTE *mem;

        fread(&W, 2, 1, F);
        fread(&H, 2, 1, F);
        fseek(F, 0, SEEK_END);
        flen = ftell(F);
        rewind(F);
        if (flen == 4 + W * H * 3)
          C = 3;
        else if (flen == 4 + W * H * 4)
          C = 4;
        if (flen == 4 + W * H)
          C = 1;
        mem = new BYTE[W * H * C];
        if (C != 0)
        {
          fread(mem, C, W * H, F);
          res = AddImg(TexName, W, H, C, mem);

          delete[] mem;
        }
        fclose(F);
      }
    }
  }
  
  return res;
}

int resources::FindTexture( std::string name )
{
  int TexNo = -1;
  for (int i = 0; i < NumOfTextures; i++)
  {
    if (name == tex[i].Name)
    {
      TexNo = i;
    }
  }
  return TexNo;
}