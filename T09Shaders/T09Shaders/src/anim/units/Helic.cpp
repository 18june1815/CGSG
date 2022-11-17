#include "Units.h"



Helic::Helic( render *R )
{
  rnd = R;
  Prim.MtlNo = 0;
  Prim.LoadNew("bin/models/Mi28.obj");
  //Prim.Load("bin/models/Mi28.obj");
  //SetMaterial();
  //Prim.SetWorldTransormation(dlgl::matr::Scale({5, 8, 5}));
  //Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3{1.5, 1.7, 1.5}));
  
  rnd->cam.Loc = dlgl::vec3{0.0, 1.0, -3.0};
  rnd->cam.At = Pos;
  //rnd->cam.At = dlgl::vec3{0.0, 0.0, 7.0};
}

void Helic::SetMaterial( void )
{
  material m = material::GetLibMaterial("Chrome");
  m.Name = "Helic";
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
}


void Helic::Draw( dlgl::matr MatrVP  ) 
{
  Prim.Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd);
}

void Helic::Response( void )
{
/*  float dt;
  dt = rnd->T.DeltaTime;

  dPos = Dir * Speed;
  float a = Dir.Angle(OldDir);
  OldDir = Dir;

  Prim.SetWorldTransormation(dlgl::matr::Translate(-Pos));
  Prim.SetWorldTransormation(dlgl::matr::RotateY( Sign * a ));
  Prim.SetWorldTransormation(dlgl::matr::Translate(Pos + dPos));

  rnd->cam.Loc -= Pos;
  rnd->cam.Loc = dlgl::matr::RotateY(Sign * a).PointTransform(rnd->cam.Loc); 
  rnd->cam.Loc += (Pos + dPos);

  Pos += dPos;
  rnd->cam.At = Pos;
  */
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
    Speed += 0.03;
    break;

  case VK_DOWN:
    if (Speed > 0)
      Speed -= 0.03;
    break;

  case VK_PRIOR:
    dPos.Y += 0.05;
    break;

  case VK_NEXT:
    dPos.Y -= 0.05;
    break;

  case VK_SPACE:
    Speed = 0;
    break;
  }
}