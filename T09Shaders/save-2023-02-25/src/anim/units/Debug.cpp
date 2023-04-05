#include "Units.h"


debug::debug( render *R, camera *c )
{
  name = "debug";
  rnd = R;
  cam = c;

  material m = material::DefMaterial();
  m.Name = "debug";
  m.ShdNo = rnd->resources->AddShader("debug") - 1;

  Prim.Create(NULL, 1, NULL, 0);
  Prim.MtlNo = rnd->resources->AddMaterial(&m) - 1;    
}


void debug::Draw( dlgl::matr MatrVP  ) 
{
  Prim.Draw(PolygonMode, GL_POINTS, MatrVP, rnd, cam);
}

void debug::Response( void )
{
}                                   
                                                             