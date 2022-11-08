#ifndef __GRID_H_
#define __GRID_H_

#include "../rnd/prim.h"


class grid
{
public:
  int W, H; //Grid size (in verices)
  prim Prim;
  std::vector<vertex> V;

  grid( int w, int h );
  ~grid()
  {
  }

  void AutoNormals( void );
  void PrimFromGrid( prim &Prim );
  bool CreateSphere( float R );
  void Draw( dlgl::matr MatrVP );
};

#endif /* __GRID_H_ */

