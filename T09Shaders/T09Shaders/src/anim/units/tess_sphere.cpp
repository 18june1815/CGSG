#include "Units.h"


tess_sphere::tess_sphere( render *R, camera *c )
{
  name = "tess_sphere";
  rnd = R;
  cam = c;

  material m = material::DefMaterial();
  m.Name = "tess_sphere line material";
  m.ShdNo = rnd->resources.AddShader("tess_sphere") - 1;

  vertex v[1] = 
  {
    {{0, 0, 0}}
  };

  int Ind[1] = {0};
  //Prim.Create(v, 4, Ind, 4);
  Prim.Create(v, 1, Ind, 1);
  Prim.NumOfPatchPoints = 1;
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;    
}


void tess_sphere::Draw( dlgl::matr MatrVP  ) 
{
  glPointSize(4);
  Prim.Draw(PolygonMode, GL_PATCHES, MatrVP, rnd, cam);
  //Prim.Draw(PolygonMode, GL_POINTS, MatrVP, rnd, cam);
}

void tess_sphere::Response( void )
{
}