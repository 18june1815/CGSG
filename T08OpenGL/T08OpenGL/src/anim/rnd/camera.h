#ifndef __CAMERA_H_
#define __CAMERA_H_

namespace rnd
{
  class camera : public object
  {
  public:
    dlgl::vec3 
      Loc, // Location of the camera
      At, // Position of subject
      Up, // Approximate Up direction
      Dir, //Direction of view
      Right;
    dlgl::matr MatrWorld; //Camera World Transformation
    int LastMousePos[2];


    camera ( void ): Loc(dlgl::vec3(2,2,2)), At(dlgl::vec3(0,0.1,0)), Up(dlgl::vec3(0,1,0)),
                     MatrWorld(dlgl::matr::Identity())
    {
      LastMousePos[0] = 0; //Last X mouse position 
      LastMousePos[1] = 0; //Last Y mouse position 
      Dir = (At - Loc).Normalize();
      Right = (Dir.Cross(Up)).Normalize();
    }

    void SetLoc( dlgl::vec3 L )
    {
      Loc = L;
    }
    void SetAt( dlgl::vec3 A )
    {
      At = A;
    }
    void Render( void ) override
    {
      MatrView = dlgl::matr::View(Loc, At, Up);
      MatrView = MatrView * MatrWorld;
      MatrVP = MatrView * MatrProj;
    }                   

    void MouseWheel( void ) override
    {
      static int wheelDelta = 0;
      wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
      if (wheelDelta > 0)
      {
        Loc = Loc - Dir;
      }
      else if (wheelDelta < 0)
      {
        Loc = Loc + Dir;
      }
    }

    void MouseMove( void ) override
    {
      int l1,l2;

      l1 = LOWORD(lParam);
      l2 = HIWORD(lParam);
  
      if (abs(l1 - LastMousePos[0]) > FrameW / 10)
        LastMousePos[0] = l1;
      if (abs(l2 - LastMousePos[1]) > FrameH / 10)
        LastMousePos[1] = l2;
      MatrWorld = MatrWorld * dlgl::matr::Rotate(Up, (l1 - LastMousePos[0]) * 0.1);
      MatrWorld = MatrWorld * dlgl::matr::Rotate(dlgl::vec3(1, 0, 0), (l2 - LastMousePos[1]) * 0.1);

      LastMousePos[0] = l1;
      LastMousePos[1] = l2;

      Ellipse(hDC, LOWORD(lParam) - 30, HIWORD(lParam) - 30, LOWORD(lParam) + 30, HIWORD(lParam) + 30);
    }
  };
}
#endif /* __CAMERA_H_*/