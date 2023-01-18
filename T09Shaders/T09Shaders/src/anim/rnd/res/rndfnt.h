#ifndef __RNDFNT_H_
#define __RNDFNT_H_ 

#include <fstream>
#include "def.h"
#include "rndres.h"
#include "../prim.h"
#include "../grid.h"


struct fontStruct 
{
  DWORD LineH, BaseH;
  float AdvanceX[256];
};

class font 
{
public:
  fontStruct Fnt;
  int FntMtlNo;
  prim *primitives[256];
  render *rnd;  
  camera *cam;

  font( render *R, camera *c )
  {
    rnd = R;
    cam = c;
    Load("bin/fonts/Book.g3df");
  }
  void Delete( void )
  { 
    for (int i = 0; i < 256; i++)
    {
      primitives[i]->Delete();  
      delete[] primitives[i];
    }
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


    FILE *F;
    if ((F = fopen(FileName, "rb")) == NULL)
      return false;
    fread(&Sign, 4, 1, F);
 
    if (Sign != *(DWORD *)"G3DF")
      return false;
    fread(&Fnt, sizeof(fontStruct), 1, F);
    fread(Chars, sizeof(Chars), 1, F);
    fread(&W, 4, 1, F);
    fread(&H, 4, 1, F);
    //F.read(&Fnt, )
    
    tex = new DWORD[W * H * 4];     
    fread(tex, 4, W * H, F);

    material mtl;
    mtl = material::DefMaterial();
    mtl.Name = FileName;
    mtl.Ka = dlgl::vec3(0, 0, 1);
    mtl.Tex[0] = rnd->resources.AddImg(FileName, W, H, 4, (BYTE*)tex);
    delete[] tex;
    mtl.ShdNo = rnd->resources.AddShader("font") - 1;

    FntMtlNo = rnd->resources.AddMaterial(&mtl);

    for (int i = 0; i < 256; i++)
    {
      vertex v[4];

      for (int k = 0; k < 4; k++)
        v[k].P = Chars[i][k].P, v[k].T = Chars[i][k].T,
        v[k].N = dlgl::vec3(0, 0, 1), v[k].C = dlgl::vec4(1, 1, 1, 1); 

      primitives[i] = new prim();
      //grid g(10, 10);
      //g.PrimFromGrid(*primitives[i]);
      int Ind[4] = {0, 1, 2, 3};
      primitives[i]->Create(v, 4, Ind, 4);
  
      primitives[i]->MtlNo = FntMtlNo - 1;
  
    }
    return true;
  }
  
  void Draw( char *Str, dlgl::vec3 Pos, float Size, int PolygonMode )
  {
    dlgl::vec3 p = Pos;

    dlgl::matr
      Proj = dlgl::matr::Frustum(-10, 10, -10, 10, -1, 1),
      View = dlgl::matr::Identity(),
      MatrVP = View * Proj;
    while (*Str != 0)
    {
      if (*Str == '\n')
        Pos.X = p.X, Pos.Y -= Size;
      else
        if (Fnt.AdvanceX[(UCHAR)*Str] != 0)
        {
          primitives[(UCHAR)*Str]->Draw(GL_FILL, GL_TRIANGLE_STRIP, MatrVP, rnd, cam);
          dlgl::matr 
            M = dlgl::matr::Scale({Size, Size, 1}) * dlgl::matr::Translate(Pos);
          primitives[(UCHAR)*Str]->MatrWorld = M;
          Pos.X += Fnt.AdvanceX[(UCHAR)*Str] * Size;
        }
      Str++;

    }
  }
};



#endif /* __RNDFNT_H_ */