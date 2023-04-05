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
  void Delete( void );
  bool Load( const char *FileName );
  void Draw( char *Str, dlgl::vec3 Pos, float Size, int PolygonMode );
};


#endif /* __RNDFNT_H_ */