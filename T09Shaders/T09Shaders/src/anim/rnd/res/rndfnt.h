#ifndef __RNDFNT_H_
#define __RNDFNT_H_ 

#include <fstream>
#include "def.h"
#include "rndres.h"
#include "../prim.h"
#include "../grid.h"

#if 0
struct fontStruct
{
  DWORD LineH, BaseH;
  float AdvanceX[256];
};
class font 
{
public:
  static fontStruct Fnt;
  static prim FntChars[256];
  static int FntMtlNo;
  prim *primitives[256];

  font( void )
  {
    Load("bin/fonts/book.g3df");
  }
  ~font ( void )
  {
    for (int i = 0; i < 256; i++)
      FntChars[i].Delete();
  }

  bool Load( const char *FileName )
  {
    DWORD Sign, W, H, *tex;
    struct 
    {
      dlgl::vec3 P; //Char endpoint position
      dlgl::vec2 T; //Char endpoint texture coordinates
      dlgl::vec3 N; //Char endpoint normal (not used)
      dlgl::vec4 C; //Char endpoint color (not used)
    } Chars[256][4];

    material mtl;
    //std::fstream F(FileName, std::ios::in | std::ios::binary);
    //if (!F)
    //  return false;

  
    //F.read((char *)Sign, 4);
      FILE *F;
    if (Sign != *(DWORD *)"G3DF")
      return false;
    fread(&Fnt, sizeof(fontStruct), 1, F);
    fread(Chars, sizeof(Chars), 1, F);
    fread(&W, 4, 1, F);
    fread(&H, 4, 1, F);
    
    float *tex = new float(W * H * 4);     //?
    fread(tex, 4, W * H, F);

    mtl = material::DefMaterial();
    mtl.Name = FileName;
    mtl.Tex[0] = rnd->resources.AddImg(FileName, W, H, 4, tex);
    free(tex);
    mtl.ShdNo = rnd->resources.AddShader("font");

    FntMtlNo = rnd->resources.AddMaterial(&mtl);

    for (int i = 0; i < 256; i++)
    {
      vertex v[4];

      for (int k = 0; k < 4; k++)
        v[k].P = Chars[i][k].P, v[k].T = Chars[i][k].T,
        v[k].N = dlgl::vec3(0, 0, 1), v[k].C = dlgl::vec4(1, 1, 1, 1); 

      primitives[i] = new prim();
      grid g(W, H);
      g.PrimFromGrid(*primitives[i]);
  
      primitives[i]->MtlNo = FntMtlNo;
  
    }
    return true;
  }
  
  void Draw( char *Str, dlgl::vec3 Pos, float Size )
  {
    dlgl::vec3 p = Pos;

    while (*Str != 0)
    {
      if (*Str == '\n')
        Pos.X = p.X, Pos.Y -= Size;
      else
        if (Fnt.AdvanceX[(UCHAR)*Str] != 0)
        {
          FntChars[(UCHAR)*Str].Draw(GL_FILL, GL_TRIANGLE_STRIP, MatrVP, rnd, cam);

        }
      Str++;

    }
  }
};

#endif

#endif /* __RNDFNT_H_ */