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
  camera *cam;
  dlgl::matr MatrWorld;  //World tranformation matrix
  const char *FileName; //File name to Load prim
  prim *primitives[MAX_PRIMITIVES];
  int NofElements = 0;
  dlgl::vec3 MinBB, MaxBB;

  prims( void ) : MatrWorld(dlgl::matr::Identity()), FileName("")
  {
    MinBB = dlgl::vec3(0, 0, 0);
    MaxBB = dlgl::vec3(0, 0, 0);
  }

  // For G3DM
  prims( render *R, camera *c ) : MatrWorld(dlgl::matr::Identity()), FileName("")
  {
    rnd = R;
    cam = c;
  }

  bool FindStartLines( std::vector<int> &lineNo, const char *FileName );
  bool Load( const char *FileName );
  void Delete( void );
  void SetWorldTransormation( const dlgl::matr &MW );
  void SetMatrWorld( const dlgl::matr &MW );
  bool LoadG3DM( const char *FileName );
  void Draw( dlgl::matr MatrVP );
  void SetBB( void );
  void EvalBB( vertex *V, int NoofV );
};

#endif /* __PRIMS_H_ */
