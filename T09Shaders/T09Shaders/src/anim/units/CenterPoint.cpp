#include "Units.h"
#include "../rnd/grid.h"  

CenterPoint::CenterPoint( render *Rnd )
{
  rnd = Rnd;
  int W = 10, H = 10;
  float R = 0.01;
  grid g(W, H);

  g.CreateSphere(R);

  g.PrimFromGrid(Prim);
  SetMaterial();

  //rnd->cam.Loc = dlgl::vec3(0., 0.2, 0.);
  //rnd->cam.At = dlgl::vec3(0., 0., 0.);
  Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3(0,0.0,0)));
}

void CenterPoint::Draw( dlgl::matr MatrVP )
{
  Prim.Draw(GL_FILL, GL_TRIANGLE_STRIP, MatrVP, rnd);
}


void CenterPoint::SetMaterial( void )
{ 
  material m = material::DefMaterial();
  m.Ka = dlgl::vec3(1, 0, 0);
  m.Name = "CenterPoint";
  //rnd->resources.AddTexture(&m, m.Name, "bin/textures/CenterPoint_sphere.bmp");
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
}

