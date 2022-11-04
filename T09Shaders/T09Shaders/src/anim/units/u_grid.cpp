#include "Units.h"
#include "../rnd/grid.h"  

u_grid::u_grid()
{
  int W = 30, H = 30, R = 1.;
  grid g(W, H);

  g.CreateSphere(R);
  g.PrimFromGrid(Prim);
}

void u_grid::Draw( dlgl::matr MatrVP )
{
  Prim.Draw(GL_LINE, GL_TRIANGLE_STRIP, MatrVP);
}


void u_grid::SetMaterial( void )
{
  material m = material::DefMaterial();
  float
    R1 = (float) rand()/RAND_MAX,
    R2 = (float) rand()/RAND_MAX,
    R3 = (float) rand()/RAND_MAX;
  dlgl::vec3 color = dlgl::vec3(R1, R2, R3);
  m.Ka = color * 0.1;
  m.Kd = color * 0.8;
  m.Ks = color * 0.9;
  m.Ph = 50;
  Prim.MtlNo = rnd.resources.AddMaterial(&m) - 1;
}