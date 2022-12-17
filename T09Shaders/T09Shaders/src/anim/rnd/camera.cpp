#include "camera.h"

camera::camera ( render *R, input *I ): Loc(dlgl::vec3(20, 1, 2)), At(dlgl::vec3(0,1,0)), Up(dlgl::vec3(0,1,0)),
                  MatrWorld(dlgl::matr::Identity())
{
  LastMousePos[0] = 0; //Last X mouse position 
  LastMousePos[1] = 0; //Last Y mouse position 
  Dir = (At - Loc).Normalize();
  ViewDir = Dir;
  Right = (Dir.Cross(Up)).Normalize();
  rnd = R;
  Inp = I;
}

void camera::Draw( dlgl::matr &MatrView, dlgl::matr &MatrVP, dlgl::matr &MatrProj ) 
{
  MatrView = dlgl::matr::View(Loc, At, Up);
  MatrView = MatrView * MatrWorld;
  MatrVP = MatrView * MatrProj;
}                   

void camera::SetWorldTransormation( const dlgl::matr &MW )
{
  MatrWorld = MatrWorld * MW;
}

void camera::Control( void )
{
  float dT = 1;
  float Dist, cosT, sinT, plen, cosP, sinP, Azimuth, Elevator;

  rnd->MatrView = dlgl::matr::View(Loc, At, Up);

  Right = dlgl::vec3(rnd->MatrView.M[0][0], rnd->MatrView.M[1][0], rnd->MatrView.M[2][0]);
  Up    = dlgl::vec3(rnd->MatrView.M[0][1], rnd->MatrView.M[1][1], rnd->MatrView.M[2][1]);
  Dir   = dlgl::vec3(rnd->MatrView.M[0][2], rnd->MatrView.M[1][2], rnd->MatrView.M[2][2]);

  rnd->MatrVP = MatrWorld * rnd->MatrView * rnd->MatrProj;

  if (Inp->Keys[VK_CONTROL] != 0)
  {

    Dist = !(At - Loc);

    cosT = (Loc.Y - At.Y) / Dist;
    sinT = sqrt(1 - cosT * cosT);

    plen = Dist * sinT;
    cosP = (Loc.Z - At.Z) / plen;
    sinP = (Loc.X - At.X) / plen;

    Azimuth = mth::R2D(atan2(sinP, cosP));
    Elevator = mth::R2D(atan2(sinT, cosT));

    Azimuth += dT *
      (-3 * Inp->Keys[VK_LBUTTON] * Inp->Mdx +
        5 * (Inp->Keys[VK_LEFT] - Inp->Keys[VK_RIGHT]));
    
    Elevator += rnd->T.GlobalDeltaTime * 
      (-3 * Inp->Keys[VK_LBUTTON] * Inp->Mdx +
        5 * (Inp->Keys[VK_UP] - Inp->Keys[VK_DOWN]));
    if (Elevator < 0.1)
      Elevator = 0.1;
    else if (Elevator > 179.90)
      Elevator = 179.9;

    Dist += rnd->T.GlobalDeltaTime * 
      (Inp->Mdz * 0.008 + 6 * (Inp->Keys[VK_NEXT] - Inp->Keys[VK_PRIOR]));
    if (Dist < 0.1)
      Dist = 0.1;

  
    // Handle camera position
    if (Inp->Keys[VK_RBUTTON])
    {
      float Wp = rnd->ProjSize;
      float Hp = rnd->ProjSize;
      if (rnd->FrameW > rnd->FrameH)
        Wp *= (float) rnd->FrameW / rnd->FrameH;
      else
        Hp *= (float) rnd->FrameH / rnd->FrameW;

      float sx = -Inp->Mdx * Wp / rnd->FrameW * Dist / rnd->ProjDist;
      float sy = Inp->Mdy * Hp / rnd->FrameH * Dist / rnd->ProjDist;

      dlgl::vec3 dv = Right * sx + Up * sy;
      At = At + dv;
      Loc = Loc + dv;
  
    }
    dlgl::matr W = dlgl::matr::RotateZ(Elevator) *
                   dlgl::matr::RotateY(90 - Azimuth) *
                   dlgl::matr::Translate(At);
   

    Loc = W.PointTransform(dlgl::vec3{0, Dist, 0 });

    Up = dlgl::vec3{0, 1, 0};
    Draw(rnd->MatrView, rnd->MatrVP, rnd->MatrProj);

  }
}