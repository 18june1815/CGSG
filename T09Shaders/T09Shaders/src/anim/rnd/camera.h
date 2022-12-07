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


  camera ( void ): Loc(dlgl::vec3(20, 1, 2)), At(dlgl::vec3(0,1,0)), Up(dlgl::vec3(0,1,0)),
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


  void Draw( dlgl::matr &MatrView, dlgl::matr &MatrVP, dlgl::matr &MatrProj ) 
  {
    MatrView = dlgl::matr::View(Loc, At, Up);
    MatrView = MatrView * MatrWorld;
    MatrVP = MatrView * MatrProj;
  }                   

  void SetWorldTransormation( const dlgl::matr &MW )
  {
    MatrWorld = MatrWorld * MW;
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

    
  
  
  }


  /*
  void Set ( render *rnd, int Keys[30], int Mdx, float Mdz )
  {
    float dT = 1;
    float Dist, cosT, sinT, plen, cosP, sinP, Azimuth, Elevator;

    rnd->MatrView = dlgl::matr::View(Loc, At, Up);
    
    Right = dlgl::vec3(rnd->MatrView.M[0][0], rnd->MatrView.M[1][0], rnd->MatrView.M[2][0]);
    Up    = dlgl::vec3(rnd->MatrView.M[0][1], rnd->MatrView.M[1][1], rnd->MatrView.M[2][1]);
    Dir   = dlgl::vec3(rnd->MatrView.M[0][2], rnd->MatrView.M[1][2], rnd->MatrView.M[2][2]);

    rnd->MatrVP = rnd->MatrView * rnd->MatrProj;

    Dist = !(At - Loc);

    cosT = (Loc.Y - At.Y) / Dist;
    sinT = sqrt(1 - cosT * cosT);

    plen = Dist * sinT;
    cosP = (Loc.Z - At.Z) / plen;
    sinP = (Loc.X - At.X) / plen;

    Azimuth = mth::R2D(atan2(sinP, cosP));
    Elevator = mth::R2D(atan2(sinT, cosT));

    Azimuth += dT *
      (-30 * Keys[VK_LBUTTON] * Mdx +
        47 * (Keys[VK_LEFT] - Keys[VK_RIGHT]));
    
    Elevator += rnd->T.GlobalDeltaTime * 
      (-30 * Keys[VK_LBUTTON] * Mdx +
        47 * (Keys[VK_UP] - Keys[VK_DOWN]));
    if (Elevator < -89.90)
      Elevator = -89.9;
    else if (Elevator > 89.90)
      Elevator = 89.9;

    Dist +=  rnd->T.GlobalDeltaTime * 
      (Mdz + (Keys[VK_NEXT] - Keys[VK_PRIOR]));

    if (Dist < 0.1)
      Dist = 0.1;

    // Handle camera position
    float Wp = rnd->ProjSize;
    float Hp = rnd->ProjSize;
    if (rnd->FrameW > rnd->FrameH)
      Wp *= (float) rnd->FrameW / rnd->FrameH;
    else
      Hp *= (float) rnd->FrameH / rnd->FrameW;

    float sx = Wp / rnd->FrameW * Dist / rnd->ProjDist;
    float sy = Hp / rnd->FrameH * Dist / rnd->ProjDist;

    dlgl::vec3 dv = Right * sx + Up * sy;
    At = At + dv;
    Loc = Loc + dv;

  }
    */
};

#endif /* __CAMERA_H_*/