#ifndef __RNDPRIM_H_
#define __RNDPRIM_H_

#include "rnd/rnd.h"
#include "anim.h"

namespace rnd
{
  struct vertex
  {
    dlgl::vec3 P;
  };

  class prim : public object
  {
  public:
    vertex *V;   // Vertex attributes array
    int NumOfV;  // Number of vertices                           
    int *I;      // Index array (for trimesh - by 3 ones)
    int NumOfI;  // Number of indices
    dlgl::matr MatrWorld;  //World tranformation matrix
    const char *FileName; //File name to Load prim

    dlgl::vec3 MinBB, MaxBB; // Bound box

    prim( const char *FN ) :
      V(nullptr), I(nullptr), NumOfV(0), NumOfI(0),
      MatrWorld(dlgl::matr::Identity()), FileName(FN)
    {
      Load(FileName);
      SetBB();
    }

    prim( void ) :
      V(nullptr), I(nullptr), NumOfV(0), NumOfI(0),
      MatrWorld(dlgl::matr::Identity()), FileName("")
    {
 
    }
    ~prim( void )
    {
      if (V != nullptr)
        delete[] V;
      if (I != nullptr)
        delete[] I;
    }

    bool Create( int NoofV, int NoofI );
    void Response( void ) override;
    void Render( void ) override;
    void SetWorldTransormation( dlgl::matr MatrWorld );
    void EvalBB( void );
    void SetBB( void );
    bool Load( const char *FileName );

   
  };  // end of class "prim"
}
#endif /* __RNDPRIM_H_*/
