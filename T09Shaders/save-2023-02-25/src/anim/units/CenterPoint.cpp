#include "Units.h"
#include "../rnd/grid.h"  

CenterPoint::CenterPoint( render *Rnd, camera *c )
{
  name = "CentralPoint";
  cam = c;
  rnd = Rnd;
  int W = 10, H = 10;
  float R = 0.1;
  grid g(W, H);

  g.CreateSphere(R);

  g.PrimFromGrid(Prim);
  SetMaterial();

  Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3(0,0,0)));
  //Prim.SetWorldTransormation(dlgl::matr::Scale(dlgl::vec3(0,0,0)));
}


void CenterPoint::Draw( dlgl::matr MatrVP )
{
  Prim.Draw(PolygonMode, GL_TRIANGLE_STRIP, MatrVP, rnd, cam);
  //dlgl::matr M = dlgl::matr::Translate({0.7, 0, 0});
  //Prim.Draw(PolygonMode, GL_TRIANGLE_STRIP, M * MatrVP, rnd, cam);
}


void CenterPoint::SetMaterial( void )
{ 
  material m = material::DefMaterial();
  m.Ka = dlgl::vec3(1, 0, 0);
  m.Name = "CenterPoint";
  //rnd->resources->AddTexture(&m, m.Name, "bin/textures/CenterPoint_sphere.bmp");
  Prim.MtlNo = rnd->resources->AddMaterial(&m) - 1;
}

