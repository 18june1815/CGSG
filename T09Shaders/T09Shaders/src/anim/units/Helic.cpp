#include "Units.h"


void Helic::Delete( void )
{
  Prims.Delete();
}


Helic::Helic( render *R )
{
  name = "Helic";
  rnd = R;
  //Mounts = m;

  Prim.MtlNo = 0;
  
  //Prim.Load("bin/models/Mi28.obj");
  //SetMaterial();
  //Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3{1.5, 1.7, 1.5}));

  Prims.Load("bin/models/Mi28.obj");


   dlgl::vec3 centr = dlgl::vec3(0, 0, 0.7);
   Prims.SetWorldTransormation(dlgl::matr::Translate(centr));

     Prims.SetWorldTransormation(Scale);

  //dlgl::vec3 centr = dlgl::vec3(0, 0, 0.68);
  //Prims.primitives[2]->SetWorldTransormation(dlgl::matr::Translate(-centr * 0.05));

  //dlgl::vec3 centr = dlgl::vec3(-0.1, 0.04, -0.234);
  //Prims.primitives[4]->SetWorldTransormation(dlgl::matr::Translate(-centr ));

   Prims.SetWorldTransormation(dlgl::matr::RotateY( Sign * 5 ));
   Dir = dlgl::matr::RotateY(5).PointTransform(Dir);    
  rnd->cam.Loc = dlgl::vec3{0.5, 0.0, 0.};
  rnd->cam.At = dlgl::vec3{0.0, 0.0, 0.0};
  //rnd->cam.Loc = dlgl::vec3{0., 1, -0.2};
  //rnd->cam.At = dlgl::vec3{0.0, 0.0, 0.2};
 
  //rnd->cam.At = Pos;
  //rnd->cam.Loc = dlgl::vec3{0.0, 0.2, -0.5};
}

void Helic::SetMaterial( void )
{
  material m = material::GetLibMaterial("Chrome");
  m.Name = "Helic";
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
}


void Helic::Draw( dlgl::matr MatrVP  ) 
{
  //Prim.Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd);
  for (int i = 0; i < Prims.NofElements; i++)
  {
    Prims.primitives[i]->Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd);
  }
  // Prims.primitives[4]->Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd);
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
  float dt, RotationZ = 0, RotationX = 0;
  dt = rnd->T.DeltaTime;

  dPos.X = (Dir * Speed).X;
  dPos.Z = (Dir * Speed).Z;
  float a = Dir.Angle(OldDir);
  OldDir = Dir;
  
  dAngles.Y = a;
  
  CourseSpeed += 5;
  CourseSpeed *= 1 - dt * 10;

  //dAngles.Z = CourseSpeed - Sign * 0.1 * Angles.Z;
  ////zAngle += Sign * RotationZ;
  //Angles.Z = Sign * RotationZ;
  RotationZ = CourseSpeed - Sign * 0.1 * zAngle;
  zAngle += Sign * RotationZ;

  if (abs(zAngle) >= 30)
  {
    RotationZ = 0;
    zAngle = zAngle / abs(zAngle) * 10;
  }

  RotationX += (dPos & Dir) * 80;
  RotationX -= 0.5 * xAngle;

  xAngle += Sign * RotationX;

  if (xAngle >= 10)
  {
    RotationX = 0;
    xAngle = 10;
  }

  dlgl::matr M = Prims.MatrWorld;
  Prims.SetWorldTransormation( M.Inverse());
  BladesRotationX();
  BladesRotationY();

  //Prims.SetWorldTransormation(dlgl::matr::RotateY( Sign * 5 ));
  //Prims.SetWorldTransormation(dlgl::matr::Rotate(Dir, -Sign * 3));
  Prims.SetWorldTransormation(dlgl::matr::Rotate(Dir, -Sign * RotationZ));
  //Prims.SetWorldTransormation(dlgl::matr::RotateX(-RotationX));
  Prims.SetWorldTransormation(M);
  //Prims.SetWorldTransormation(dlgl::matr::Translate(dPos));
  
  //rnd->cam.Loc -= Pos;
  //rnd->cam.Loc = dlgl::matr::RotateY(Sign * a).PointTransform(rnd->cam.Loc); 
  //rnd->cam.Loc += (Pos + dPos);
  //
  //Pos += dPos;
  //rnd->cam.At = Pos;
}

void Helic::Keyboard( WPARAM wParam )
{
  
  switch (wParam)
  {
  case VK_RIGHT:
    Sign = 1;
    Dir = dlgl::matr::RotateY(5).PointTransform(Dir);    
    break;

  case VK_LEFT:
     Sign = -1;
     Dir = dlgl::matr::RotateY(-5).PointTransform(Dir);    
    break;

  case VK_UP:
    Speed += 0.001;
    break;

  case VK_DOWN:
    if (Speed > 0)
      Speed -= 0.001;
    break;

  case VK_PRIOR:
    dPos.Y += 0.1;
    break;

  case VK_NEXT:
    dPos.Y -= 0.1;
    break;

  case VK_SPACE:
    Speed = 0;
    break;
  }
}


void Helic::Collisions( void )
{
  std::vector<dlgl::vec3> V;
  V = Mounts->Pmounts;

  //if (Pos.Y < )
}