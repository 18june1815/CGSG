#ifndef __PRIM_H_
#define __PRIM_H_

#include "mth/mth.h"

#include "rnd.h"
#include "camera.h"

struct vertex
{
  dlgl::vec3 P; // Position
  dlgl::vec2 T; // Texture coordinate
  dlgl::vec3 N; //Normal
  dlgl::vec4 C; //Color
};

class prim 
{
public:
  //OpenGL specific data
  UINT 
    VA, VBuf, //Vertex array and vertex bubber number
    IBuf;     //Index buffer number
  int NumOfElements, //Number of elements (indexes or vertexes)
      NumOfV; // Number of vertexes

  int MtlNo = 0;  //Material number in material array
  dlgl::matr Trans;

  dlgl::matr MatrWorld;  //World tranformation matrix
  const char *FileName; //File name to Load prim

  dlgl::vec3 MinBB, MaxBB, center; // Bound box


  prim( void ) :
    VA(0), VBuf(0), NumOfElements(0),
    MatrWorld(dlgl::matr::Identity()), FileName(""),
    MinBB({0,0,0}), MaxBB({0, 0, 0}), center({0, 0, 0})
  {
  //  LoadTriangle();
  }
  //~prim( void );
  void Create( vertex *V, int NoofV, int *Ind, int NoofI );
  void Delete( void );
  virtual void Draw( int PolygonMode, int ElementsMode, const dlgl::matr &MatrVP, render *rnd, camera *cam );
  virtual void SetMaterial( void );
  void SetWorldTransormation( const dlgl::matr &MatrWorld );
  void EvalBB( vertex *V, int NoofV );
  void SetBB( vertex *V, int NoofV );
  bool Load( const char *FileName );
  bool Load( const char *FileName, int lineStart, int lineStop, int sum );
  bool LoadNew( const char *FileName );
  void Autonormals( vertex *V, int NoofV, int *Ind, int NoofI );
  bool LoadTriangle( void );
};

#endif /* __PRIM_H_ */