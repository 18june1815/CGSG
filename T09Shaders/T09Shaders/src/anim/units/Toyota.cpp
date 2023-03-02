#include "Units.h"                                                         

Toyota::Toyota( render *R, camera *c, u_mounts *m )
{
  name = "Toyota";
  rnd = R;
  cam = c;
  Mounts = m;
  
  Prims.rnd = rnd;
  Prims.cam = cam;

  Prims.LoadG3DM("bin/models/Toyota.g3dm");

  Initial = dlgl::matr::RotateX(90);// * dlgl::matr::Translate({Prims.primitives[74]->center.X, 0, Prims.primitives[74]->center.Y});

  Mcur = dlgl::matr::Identity();
  Prims.SetMatrWorld(Initial);                          

  Dir = {0, 0, 1};
  BL = !(Prims.primitives[74]->center - Prims.primitives[70]->center);
  BW = !(Prims.primitives[69]->center - Prims.primitives[70]->center);

}

void Toyota::Delete( void )
{
  Prims.Delete();
}


void Toyota::Draw( dlgl::matr MatrVP  ) 
{
  Prims.Draw(MatrVP);
}

void Toyota::Response( void )
{
 
  // 66, 70 - front wheels
  // 74, 78 - back wheels
  int wheelN[4] = {66, 70, 74, 78};    

  int i = 0;
  for (int N : wheelN)
  {
    WheelCentr[i] = {Prims.primitives[N]->center.X, 0, -Prims.primitives[N]->center.Y};
    dlgl::matr M;
    M = Initial.Inverse() * Prims.primitives[N]->MatrWorld;
    WheelCurPos[i] = M.PointTransform(WheelCentr[i]);
    i++;
  }

  float Rlen = 0;
  if (Angle != 0)
  {
    if (Angle > 60) Angle = 60;
    Rlen = Sign * 3.8; 
    if (IsRotation == 0)
      Angle = -Angle;
  }
  
  float aZ = Dir.Angle({0, 0, 1});
  float aX = Dir.Angle({1, 0, 0});
  float a = aZ;
  if (aX < 90)
    a = 360 - aZ;

  dlgl::matr 
    RotateSpeed = dlgl::matr::RotateY(a),
    Rotate90 = dlgl::matr::RotateY(90);
  dA = 0;

  dlgl::vec3 BackWheelv = WheelCurPos[2] - WheelCurPos[3];
  dlgl::vec3 BackWheelv1 = Rotate90.VecTransform(Dir);
  Rlen = 0;
  R = dlgl::vec3(Rlen, 0, 0) - WheelCentr[3];
 
  float ac = Dir.Angle(BackWheelv);
  Pos += Dir * Speed;
  dlgl::vec3 dPos = Dir * Speed;
  i = 0;
  

  Prims.SetMatrWorld(Initial);

  Prims.SetWorldTransormation(dlgl::matr::Translate(R));
  Prims.SetWorldTransormation(RotateSpeed);
  Prims.SetWorldTransormation(dlgl::matr::Translate(-R));    
 
    
  Prims.SetWorldTransormation(dlgl::matr::Translate({Pos.X, 0, Pos.Z}));
  Mcur = Initial.Inverse() * Prims.MatrWorld;

  i = 0;
  for (int N : wheelN)
  {
    WheelCurPos[i] = Mcur.PointTransform(WheelCentr[i]);
    Prims.primitives[N]->SetWorldTransormation(dlgl::matr::Translate({0, Mounts->GetHeight(WheelCurPos[i]),0}));
    Prims.primitives[N - 3]->SetWorldTransormation(dlgl::matr::Translate({0, Mounts->GetHeight(WheelCurPos[i]),0}));
    Prims.primitives[N - 2]->SetWorldTransormation(dlgl::matr::Translate({0, Mounts->GetHeight(WheelCurPos[i]),0}));
    Prims.primitives[N - 1]->SetWorldTransormation(dlgl::matr::Translate({0, Mounts->GetHeight(WheelCurPos[i]),0}));
    i++;
  }
  for (int i =0; i < Prims.NofElements; i++)
    if (i < wheelN[0] - 3 || i > wheelN[3])
      Prims.primitives[i]->SetWorldTransormation(dlgl::matr::Translate({0, Mounts->GetHeight(Pos),0})); 
}

   
void Toyota::Keyboard( BYTE Keys[256], int IsDown )
{
  
  if (!rnd->T.IsPause)
  {

    if (Keys[VK_RIGHT] && IsDown)
    {
      Sign = 1;
      Dir = dlgl::matr::RotateY(5).VecTransform(Dir);    
      Angle += 5;
      IsRotation = 1;
    }
    
 /*   if (Keys[VK_RIGHT] && !IsDown)
    {
      dA = 90;
      IsRotation = 0;
    }
   */

    if (Keys[VK_LEFT])
    {
       Sign = -1;
       Dir = dlgl::matr::RotateY(-5).VecTransform(Dir);    
       Angle -= 5;
    }

    /*
    if (Keys[VK_LEFT] && !IsDown)
    {
      dA = -90;
      IsRotation = 0;
    }
      */
    if (Keys[VK_UP])
      Speed += 0.005;

    if (Keys[VK_DOWN])
        Speed -= 0.005;
  }
}
