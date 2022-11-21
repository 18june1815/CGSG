#ifndef __PRIMS_H_
#define __PRIMS_H_

#include "mth/mth.h"

#include "prim.h"
#define MAX_PRIMITIVES 100

class prims 
{
public:

  dlgl::matr MatrWorld;  //World tranformation matrix
  const char *FileName; //File name to Load prim
  //std::vector<prim *> primitives; 
  prim *primitives[MAX_PRIMITIVES];
  int NofElements = 0;

  prims( void ) : MatrWorld(dlgl::matr::Identity()), FileName("")
  {
  }

  bool FindStartLines( std::vector<int> &lineNo, const char *FileName );
  bool Load( const char *FileName );
  void Delete( void );
  void SetWorldTransormation( const dlgl::matr &MW );
};

#endif /* __PRIMS_H_ */
