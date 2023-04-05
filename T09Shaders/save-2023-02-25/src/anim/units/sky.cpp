#include "Units.h"
#include "../rnd/grid.h"  

sky::sky( render *Rnd, camera *c )
{
  name = "sky";
  rnd = Rnd;
  cam = c;
  int W = 50, H = 50, R = 200.;
  grid g(W, H);

  g.CreateSphere(R);

  g.PrimFromGrid(Prim);
  SetMaterial();
  Prim.SetWorldTransormation(dlgl::matr::Rotate(dlgl::vec3(1, 0, 0), 180));
  Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3(0, -30, 0)));
}

void sky::Draw( dlgl::matr MatrVP )
{
  Prim.Draw(PolygonMode, GL_TRIANGLE_STRIP, MatrVP, rnd, cam);
}


void sky::SetMaterial( void )
{ 
  material m = material::DefMaterial();
  m.Name = "Sky";
  rnd->resources->AddTexture(&m, m.Name, "bin/textures/sky_sphere.bmp");
  //int TexNo = rnd->resources->AddTextureFromFile(&m, m.Name, "bin/textures/snowflake.bmp");
  //m.Tex[0] = TexNo;
  
  m.ShdNo = rnd->resources->AddShader("sky") - 1;
  Prim.MtlNo = rnd->resources->AddMaterial(&m) - 1;
}

