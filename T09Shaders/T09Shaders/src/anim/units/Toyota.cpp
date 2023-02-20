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

  //Prims.primitives[66]->SetWorldTransormation(dlgl::matr::Translate({-Prims.primitives[66]->center.X, 0, Prims.primitives[66]->center.Y}));
  //Prims.primitives[70]->SetWorldTransormation(dlgl::matr::Translate({-Prims.primitives[70]->center.X, 0, Prims.primitives[70]->center.Y}));
   //Prims.primitives[66]->SetWorldTransormation(dlgl::matr::Translate({0,5,0}));
   //Prims.SetWorldTransormation(dlgl::matr::Translate({0,5,0}));
  //Dir = Prims.primitives[74]->center - Prims.primitives[70]->center;
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
      Rlen = Sign * 3.8; // BL / std::sqrt(2 * (1 - cos(Angle)));
  //    Sign = Angle / abs(Angle);
      if (IsRotation == 0)
        Angle = -Angle;
  }
  

  float aZ = Dir.Angle({0, 0, 1});
  float aX = Dir.Angle({1, 0, 0});
  float a = aZ;
  if (aX < 90)
    a = 360 - aZ;

  dlgl::matr 
    RotateSpeed = dlgl::matr::RotateY((a + Sign * dA) * Speed),
    Rotate90 = dlgl::matr::RotateY(90);

  dA = 0;

  dlgl::vec3 BackWheelv = WheelCurPos[2] - WheelCurPos[3];
  dlgl::vec3 BackWheelv1 = Rotate90.VecTransform(Dir);
  R = dlgl::vec3(Rlen, 0, 0) - WheelCentr[3];
  //R = BackWheelv1 * Rlen - WheelCentr[3];
 
  float ac = Dir.Angle(BackWheelv);
  Pos = Dir * Speed;
  dlgl::vec3 dPos = Dir * Speed;
  i = 0;
  
  for (int N : wheelN)
  {
    Prims.primitives[N]->MatrWorld = Initial;

    if (IsRotation == 1)
    {
      Prims.primitives[N]->SetWorldTransormation(dlgl::matr::Translate(R));
      Prims.primitives[N]->SetWorldTransormation(RotateSpeed);
      Prims.primitives[N]->SetWorldTransormation(dlgl::matr::Translate(-R));    
    }
    
    //Pos = Prims.primitives[N]->MatrWorld.PointTransform({0, 0, 0}) + dPos;
  
    Prims.primitives[N]->SetWorldTransormation(dlgl::matr::Translate({Pos.X, 0,Pos.Z}));
    Prims.primitives[N]->SetWorldTransormation(Mcur);
    if ( N == 78 ) Mcur = Initial.Inverse() *  Prims.primitives[N]->MatrWorld;

    dlgl:: matr M = Initial.Inverse() * Prims.primitives[N]->MatrWorld; 
    WheelCurPos[i] = M.PointTransform(WheelCentr[i]);

    //Prims.primitives[N]->SetWorldTransormation(dlgl::matr::Translate({Pos.X, 0,Pos.Z}));
    Prims.primitives[N]->SetWorldTransormation(dlgl::matr::Translate({0, Mounts->GetHeight(WheelCurPos[i]),0}));
    i++;
  }
  
 
  
}
/*
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
      M = Prims.primitives[N]->MatrWorld * Initial.Inverse();
      WheelCurPos[i] = M.PointTransform(WheelCentr[i]);
      i++;
  }
  dlgl::vec3 BackWheelv = WheelCurPos[3] - WheelCurPos[2];   // vector between back wheels centers

  float Rlen = 0;
  Sign = 1;
  if (Angle != 0)
  {
      if (Angle > 60) Angle = 60;
      Rlen = 3.8; // BL / std::sqrt(2 * (1 - cos(Angle)));
  //    Sign = Angle / abs(Angle);
      if (IsRotation == 0)
        Angle = -Angle;
  }
  

  float aZ = Dir.Angle({0, 0, 1});
  float aX = Dir.Angle({1, 0, 0});
  float a = aZ;
  if (aX < 90)
    a = 360 - aZ;
  dlgl::matr 
    RotateSpeed = dlgl::matr::RotateY(a ),
    Rotate = dlgl::matr::RotateY( Angle),
    Rotate90 = dlgl::matr::RotateY(Sign * 90);


      if (IsRotation == 0)
      Angle = 0;
  
  if (Speed == 0)
    RotateSpeed = dlgl::matr::Identity();

  R = BackWheelv * Rlen * Sign;      //Radius
  Pos += Dir * Speed;

  i = 0;
  for (int N : wheelN)
  {
    dlgl::vec3 Centr = Prims.primitives[N]->center;
    float t = Centr.Y;
    Centr.Y = Centr.Z;
    Centr.Z = t;
  //  float R = Centr.Y - Prims.primitives[N]->MinBB.Y;

    Prims.primitives[N]->MatrWorld = Initial;
    
    if (N == 66 || N == 70)
    {
      dlgl::vec3 TFront = {-Prims.primitives[N]->center.X, 0, Prims.primitives[N]->center.Y};
      Prims.primitives[N]->SetWorldTransormation(dlgl::matr::Translate(TFront));
      Prims.primitives[N]->SetWorldTransormation(Rotate);
      Prims.primitives[N]->SetWorldTransormation(dlgl::matr::Translate(-TFront));
    }
   
    Prims.primitives[N]->SetWorldTransormation(dlgl::matr::Translate(-R));
    Prims.primitives[N]->SetWorldTransormation(RotateSpeed);
    Prims.primitives[N]->SetWorldTransormation(dlgl::matr::Translate(R));

    dlgl::matr M;
    
    Prims.primitives[N]->SetWorldTransormation(dlgl::matr::Translate({Pos.X, 0,Pos.Z}));
    
    M = Initial.Inverse() * Prims.primitives[N]->MatrWorld;
    WheelCurPos[i] = M.PointTransform(WheelCentr[i]);
    Prims.primitives[N]->SetWorldTransormation(dlgl::matr::Translate({0, Mounts->GetHeight(WheelCurPos[i]),0}));
    i++;
  }

}
*/
   
void Toyota::Keyboard( BYTE Keys[256], int IsDown )
{
  
  if (!rnd->T.IsPause)
  {

    if (Keys[VK_RIGHT] && IsDown)
    {
      //Pos = Mcur.PointTransform({0, 0, 0});
      Sign = 1;
      Dir = dlgl::matr::RotateY(5).VecTransform(Dir);    
      Angle += 5;
      IsRotation = 1;
    }
    
    if (Keys[VK_RIGHT] && !IsDown)
    {
      dA = 90;
      IsRotation = 0;
    }


    if (Keys[VK_LEFT])
    {
       //Pos = Mcur.PointTransform({0, 0, 0});
       Sign = -1;
       Dir = dlgl::matr::RotateY(-5).VecTransform(Dir);    
       Angle -= 5;
    }

    if (Keys[VK_LEFT] && !IsDown)
    {
      dA = -90;
      IsRotation = 0;
    }
 
    if (Keys[VK_UP])
      Speed += 0.005;

    if (Keys[VK_DOWN])
        Speed -= 0.005;

    /*
    if (Keys[VK_PRIOR])
      dPos.Y += 0.05;
   
    if (Keys[VK_NEXT])
      dPos.Y -= 0.05;

    if (Keys[VK_SPACE])
      Speed = 0;
  }
          */
  if (Keys['P'])
  {
     Prims.primitives[66]->SetWorldTransormation(dlgl::matr::Translate(-WheelCurPos[66]));
  }

  }
}
