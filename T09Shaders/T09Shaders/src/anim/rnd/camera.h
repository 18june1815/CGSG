#ifndef __CAMERA_H_
#define __CAMERA_H_


#include "rnd.h"
#include "Input.h"
//#include "def.h"

class camera 
{
public:
  dlgl::vec3 
    Loc, // Location of the camera
    At, // Position of subject
    Up, // Approximate Up direction 
    Dir, //Direction of view without World transformations
    ViewDir, //Direction of view with World transformations
    Right;
  dlgl::matr MatrWorld; //Camera World Transformation
  int LastMousePos[2];
  render *rnd;  
  input *Inp;

  camera ( render *R, input *I );
  void Draw( dlgl::matr &MatrView, dlgl::matr &MatrVP, dlgl::matr &MatrProj );
  void SetWorldTransormation( const dlgl::matr &MW );
  void Control( void );
};

#endif /* __CAMERA_H_*/