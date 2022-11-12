#include "Units.h"

#define Pi 3.1415926536
#define D2R(X) ((X) * Pi / 180)


Helic::Helic( render *R )
{
  rnd = R;
  Prim.MtlNo = 0;
  Prim.Load("bin/models/Mi28.obj");
  SetMaterial();
  Prim.SetWorldTransormation(dlgl::matr::Scale({5, 8, 5}));
  Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3{1.5, 1.7, 1.5}));
  
  rnd->cam.Loc = Pos + dlgl::vec3{0.0, 1.0, -9.0};
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
  float dt;
  dt = rnd->T.DeltaTime;
  
  Course += CourseSpeed * dt;
  CourseSpeed *= 1 - dt * 10;

  dPos.X = sin(D2R(Course)) * Speed * dt;
  dPos.Z = cos(D2R(Course)) * Speed * dt;
  dPos.Y *= 1 - dt * 10;

  Prim.SetWorldTransormation(dlgl::matr::Translate(-Pos));
  Prim.SetWorldTransormation(dlgl::matr::RotateY( -CourseSpeed * dt));
  Prim.SetWorldTransormation(dlgl::matr::Translate(Pos + dPos));

  Pos += dPos;
  
  rnd->cam.Loc += dPos;
  rnd->cam.At = Pos;
}

void Helic::Keyboard( WPARAM wParam )
{
  switch (wParam)
  {
  case VK_RIGHT:
    CourseSpeed += 30;
   
    break;

  case VK_LEFT:
     CourseSpeed -= 30;    
    break;

  case VK_UP:
    Speed += 0.1;

    break;

  case VK_DOWN:
    if (Speed > 0)
      Speed -= 0.3;
    break;

  case VK_PRIOR:
    dPos.Y += 0.05;
    break;

  case VK_NEXT:
    dPos.Y -= 0.05;
    break;
  }
}