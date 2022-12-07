#ifndef __PRIMS_H_
#define __PRIMS_H_

#include "mth/mth.h"

#include "prim.h"
#include "res/rndres.h"

#define MAX_PRIMITIVES 500

class prims 
{
public:

  render *rnd;
  dlgl::matr MatrWorld;  //World tranformation matrix
  const char *FileName; //File name to Load prim
  prim *primitives[MAX_PRIMITIVES];
  int NofElements = 0;

  prims( void ) : MatrWorld(dlgl::matr::Identity()), FileName("")
  {
  }

  // For G3DM
  prims( render *R ) : MatrWorld(dlgl::matr::Identity()), FileName("")
  {
    rnd = R;
  }

  bool FindStartLines( std::vector<int> &lineNo, const char *FileName );
  bool Load( const char *FileName );
  void Delete( void );
  void SetWorldTransormation( const dlgl::matr &MW );
  bool LoadG3DM( const char *FileName );
  void Draw( dlgl::matr MatrVP );
};

#endif /* __PRIMS_H_ */
