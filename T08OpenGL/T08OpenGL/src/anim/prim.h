#ifndef __RNDPRIM_H_
#define __RNDPRIM_H_

#include "rnd/rnd.h"
#include "anim.h"

namespace rnd
{
  struct vertex
  {
    dlgl::vec3 P; // Position
    dlgl::vec2 T; // Texture coordinate
    dlgl::vec3 N; //Normal
    dlgl::vec4 C; //Color
  };

  class prim : public object
  {
  public:
    //OpenGL specific data
    UINT 
      VA, VBuf, //Vertex array and vertex bubber number
      IBuf;     //Index buffer number
    int NumOfElements; //Number of elements (indexes or vertexes)

    dlgl::matr MatrWorld;  //World tranformation matrix
    const char *FileName; //File name to Load prim

    dlgl::vec3 MinBB, MaxBB; // Bound box

    prim( const char *FN ) :
      VA(0), VBuf(0), NumOfElements(0),
      MatrWorld(dlgl::matr::Identity()), FileName(FN)
    {
      Load(FileName);
    }

    prim( void ) :
      VA(0), VBuf(0), NumOfElements(0),
      MatrWorld(dlgl::matr::Identity()), FileName("")
    {
    }

    ~prim( void )
    {
      if (VA != 0)
      {
        glBindVertexArray(VA);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        if (VBuf != 0)
          glDeleteBuffers(1, &VBuf);
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &VA);
      }
      if (IBuf != 0)
        glDeleteBuffers(1, &IBuf);
    }


    void Create( vertex *V, int NoofV, int *Ind, int NoofI );
    void Response( void ) override;
    void Draw( void ) override;
    void SetWorldTransormation( dlgl::matr MatrWorld );
    void EvalBB( vertex *V, int NoofV );
    void SetBB( vertex *V, int NoofV );
    bool Load( const char *FileName );
    void Autonormals( vertex *V, int NoofV, int *Ind, int NoofI );
   
  };  // end of class "prim"
}
#endif  /* __RNDPRIM_H_*/
