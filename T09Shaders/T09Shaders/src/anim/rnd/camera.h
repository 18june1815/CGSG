#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "def.h"


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


  camera ( void ): Loc(dlgl::vec3(5,2,2)), At(dlgl::vec3(0,0.1,0)), Up(dlgl::vec3(0,1,0)),
                   MatrWorld(dlgl::matr::Identity())
  {
    LastMousePos[0] = 0; //Last X mouse position 
    LastMousePos[1] = 0; //Last Y mouse position 
    Dir = (At - Loc).Normalize();
    ViewDir = Dir;
    Right = (Dir.Cross(Up)).Normalize();
  }
  ~camera ( void )
  {
  }

  void SetLoc( dlgl::vec3 L )
  {
    Loc = L;
  }
  void SetAt( dlgl::vec3 A )
  {
    At = A;
  }
  void Draw( dlgl::matr &MatrView, dlgl::matr &MatrVP, dlgl::matr &MatrProj ) 
  {
    MatrView = dlgl::matr::View(Loc, At, Up);
    MatrView = MatrView * MatrWorld;
    MatrVP = MatrView * MatrProj;
  }                   

  void MouseWheel( WPARAM wParam )
  {
    static int wheelDelta = 0;
   
    wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam); 
    if (wheelDelta * Dir.Z > 0)
    {
      Loc = Loc - Dir * 0.1;
    }
    else if (wheelDelta * Dir.Z < 0)
    {
      Loc = Loc + Dir * 0.1;
    }
  }

  void MouseMove( WPARAM wParam, LPARAM lParam, int FrameW, int FrameH, dlgl::matr MatrView )
  {
    int l1,l2;

    l1 = LOWORD(lParam);
    l2 = HIWORD(lParam);

    if (abs(l1 - LastMousePos[0]) > FrameW / 20)
      LastMousePos[0] = l1;
    if (abs(l2 - LastMousePos[1]) > FrameH / 20)
      LastMousePos[1] = l2;
   
    dlgl::matr M = dlgl::matr::Rotate(Up, (l1 - LastMousePos[0]) * 0.1);
    Dir = dlgl::matr::Rotate(Up, (- l1 + LastMousePos[0]) * 0.1).VecTransform(Dir);
    Dir = dlgl::matr::Rotate(dlgl::vec3(1, 0, 0), ( - l2 + LastMousePos[1]) * 0.1).VecTransform(Dir);                                                                               
                  
    At = Dir + Loc;
    MatrView = dlgl::matr::View(Loc, At, Up);
   
    LastMousePos[0] = l1;
    LastMousePos[1] = l2;
  }
  
};

#endif /* __CAMERA_H_*/