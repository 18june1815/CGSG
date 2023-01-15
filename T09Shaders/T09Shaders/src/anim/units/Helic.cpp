#include "Units.h"


void Helic::Delete( void )
{
  Prims.Delete();
}


Helic::Helic( render *R, camera *c )
{
  name = "Helic";
  rnd = R;
  cam = c;

  Prim.MtlNo = 0;
  //Prims.Load("bin/models/Mi28.obj");

  Prims.rnd = rnd;
  Prims.cam = cam;
  Prims.LoadG3DM("bin/models/Mi28.g3dm");
  dlgl::vec3 centr = dlgl::vec3(0, 0, 0.7);   
  Prims.SetWorldTransormation(dlgl::matr::Translate(centr));
  Prims.SetBB();
  Prims.SetWorldTransormation(Scale);
  Prims.MinBB = Scale.PointTransform(Prims.MinBB); 
  Prims.MaxBB = Scale.PointTransform(Prims.MaxBB); 

  cam->At = Pos;
  cam->Loc = dlgl::vec3{0.0, 0.2, -0.5};
  SetMaterial();
  
}

Helic::Helic( render *R, camera *c, u_mounts *m ) : Helic::Helic(R,c)
{
  Mounts = m;
}

void Helic::SetMaterial( void )
{
  material m = material::GetLibMaterial("Chrome");
  m.Name = "Helic";
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
}


void Helic::Draw( dlgl::matr MatrVP  ) 
{
  for (int i = 0; i < Prims.NofElements; i++)
  {
    Prims.primitives[i]->Draw(PolygonMode, GL_TRIANGLES, MatrVP, rnd, cam);
  }
}

void Helic::BladesRotationY( void )
{
  dlgl::vec3 centr = dlgl::vec3(0, 0, 0.68);
  if (Prims.NofElements >= 3)
  {
    Prims.primitives[2]->SetWorldTransormation(dlgl::matr::Translate(-centr));
    Prims.primitives[2]->SetWorldTransormation(dlgl::matr::RotateY(10));
    Prims.primitives[2]->SetWorldTransormation(dlgl::matr::Translate(centr));
  }
}

void Helic::BladesRotationX( void )
{
  dlgl::vec3 centr = dlgl::vec3(-0.1 / 0.05, 0.04 / 0.05, -0.234 / 0.05);
  if (Prims.NofElements >= 5)
  {
    Prims.primitives[4]->SetWorldTransormation(dlgl::matr::Translate(-centr ));
    Prims.primitives[4]->SetWorldTransormation(dlgl::matr::RotateX(-20));
    Prims.primitives[4]->SetWorldTransormation(dlgl::matr::Translate(centr));
  }
  
}

void Helic::Response( void )
{

  float dt = rnd->T.DeltaTime;
  float a = Dir.Angle(OldDir);

  //cam->At = Pos;
  //cam->Loc = dlgl::vec3{0.0, 0.2, -0.5};

  dPos.X = (Dir * Speed).X;
  dPos.Z = (Dir * Speed).Z;
  OldDir = Dir;
  
  Angle.Y += Sign * a;
  
  CourseSpeed += a;
  CourseSpeed *= 1 - dt * 10;
  dAngle.Z = CourseSpeed + Sign * 0.1 * Angle.Z;
  Angle.Z += -Sign * dAngle.Z;

  if (abs(Angle.Z) >= 30)
    Angle.Z = Angle.Z / abs(Angle.Z) * 30;
  

  dlgl::matr M = Prims.MatrWorld;
  Prims.SetWorldTransormation( M.Inverse());

  BladesRotationX();
  BladesRotationY();

  Prims.SetWorldTransormation(Scale);
  Prims.SetWorldTransormation(dlgl::matr::RotateZ( Angle.Z));
  Prims.SetWorldTransormation(dlgl::matr::RotateY( Angle.Y ));
  Prims.SetWorldTransormation(dlgl::matr::Translate( Pos + dPos));
  
  cam->Loc -= Pos;
  cam->Loc = dlgl::matr::RotateY(Sign * a).PointTransform(cam->Loc); 
  cam->Loc += (Pos + dPos);
  
  Pos += dPos;
  cam->At = Pos;
  cam->Up = {0, 1, 0};

  Collisions();
}

void Helic::Keyboard( BYTE Keys[256] )
{
  
  if (! rnd->T.IsPause)
  {
    if (Keys[VK_RIGHT])
    {
      Sign = 1;
      Dir = dlgl::matr::RotateY(5).PointTransform(Dir);    
    }
    if (Keys[VK_LEFT])
    {
       Sign = -1;
       Dir = dlgl::matr::RotateY(-5).PointTransform(Dir);    
    }

    if (Keys[VK_UP])
      Speed += 0.001;

    if (Keys[VK_DOWN])
      if (Speed > 0)
        Speed -= 0.001;

    if (Keys[VK_PRIOR])
      dPos.Y += 0.05;
   
    if (Keys[VK_NEXT])
      dPos.Y -= 0.05;

    if (Keys[VK_SPACE])
      Speed = 0;
  }
  
  if (Keys['P'] && !rnd->T.IsPause)
  {
    float az = Dir.Angle(dlgl::vec3(0,0,1)),
          ax = Dir.Angle(dlgl::vec3(1,0,0));
    
    Sign = cos(az) * sin(az);
    cam->At = Pos;
    cam->Loc -= Pos;
    cam->Loc = dlgl::matr::RotateY(Sign * az).PointTransform(cam->Loc); 
    cam->Loc += Pos;
    cam->Up = {0, 1, 0};
  }
}


void Helic::Collisions( void )
{
  float  Hf, Hb;
  float AX, AZ;
  dlgl::vec3 dir;

  dir = Dir;
  AX = dir.Angle(dlgl::vec3(1, 0, 0));
  AZ = dir.Angle(dlgl::vec3(0, 0, 1));

  if (AX > 90) AZ = -AZ;
  dlgl::matr M = dlgl::matr::RotateY(AZ);
  dir = M.PointTransform(dir);

  M = M.Inverse(); 
  dlgl::vec3
   
    Posf = Pos + Dir * Prims.MaxBB.Z * 1.2,
    Posb = Pos + Dir * Prims.MinBB.Z * 1.2;

  
  Mounts->ToPicCoors(Posf, Hf);
  Mounts->ToPicCoors(Posb, Hb);

  if (Posf.Y - Prims.MaxBB.Y < Hf)
  {
    dPos.Y = 0;
    Speed = 0;
    Pos.Y = Hf + 0.1;
    cam->Loc.Y = Pos.Y + 0.2;
  }
  if (Posb.Y - Prims.MaxBB.Y < Hb)
  {
    dPos.Y = 0;
    Speed = 0;
    Pos.Y = Hb + 0.1;
    cam->Loc.Y = Pos.Y + 0.2;
  }
}