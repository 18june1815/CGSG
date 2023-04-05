#include "Units.h"

smoke::smoke( render *R, camera *c )
{
  name = "smoke";
  rnd = R;
  cam = c;

  material m = material::DefMaterial();
  m.Name = "smoke";
  m.Tex[0] = rnd->resources->AddTextureFromFile(&m, "smoke", "bin/textures/SMOKE.G32");
  m.ShdNo = rnd->resources->AddShader("smoke") - 1;
  
  Prim.Create(NULL, 30, NULL, 0);
  Prim.MtlNo = rnd->resources->AddMaterial(&m) - 1;
}


void smoke::Draw( dlgl::matr MatrVP  ) 
{
  glDepthMask(false);
  Prim.Draw(PolygonMode, GL_POINTS, MatrVP, rnd, cam);
  glDepthMask(true);
}
