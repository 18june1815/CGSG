#include "Units.h"

new_sky::new_sky( render *R, camera *c )
{
  name = "new_sky";
  rnd = R;
  cam = c;

  material m = material::DefMaterial();
  m.Name = "new_sky";
  rnd->resources->AddTexture(&m, "new_sky", "bin/textures/sky_sphere.bmp");
  m.ShdNo = rnd->resources->AddShader("new_sky") - 1;
  
  Prim.Create(NULL, 1, NULL, 0);
  Prim.MtlNo = rnd->resources->AddMaterial(&m) - 1;
}


void new_sky::Draw( dlgl::matr MatrVP  ) 
{
  glDepthMask(false);
  Prim.Draw(PolygonMode, GL_POINTS, MatrVP, rnd, cam);
  glDepthMask(true);
}
