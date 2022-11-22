#include "Units.h"
#include "../rnd/grid.h"  

sky::sky( render *Rnd )
{
  name = "sky";
  rnd = Rnd;
  int W = 50, H = 50, R = 100.;
  grid g(W, H);

  g.CreateSphere(R);

  g.PrimFromGrid(Prim);
  SetMaterial();
  Prim.SetWorldTransormation(dlgl::matr::Rotate(dlgl::vec3(1, 0, 0), 180));
}

void sky::Draw( dlgl::matr MatrVP )
{
  Prim.Draw(GL_FILL, GL_TRIANGLE_STRIP, MatrVP, rnd);
}


void sky::SetMaterial( void )
{ 
  material m = material::DefMaterial();
  m.Name = "Sky";
  rnd->resources.AddTexture(&m, m.Name, "bin/textures/sky_sphere.bmp");
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
}

