#include "Units.h"


tess::tess( render *R, camera *c )
{
  name = "tess";
  rnd = R;
  cam = c;

  material m = material::DefMaterial();
  m.Name = "tess line material";
  m.ShdNo = rnd->resources.AddShader("tess_line") - 1;

  vertex v[4] = 
  {
    {{-2, 0, 0}},
    {{-1, 2, 0}},
    {{1, -2, 0}},
    {{2, 0, 0}},
  };

  int Ind[4] = {0, 1, 2, 3};
  //Prim.Create(v, 4, Ind, 4);
  Prim.Create(v, 4, NULL, 0);
  Prim.NumOfPatchPoints = 4;
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;    
}


void tess::Draw( dlgl::matr MatrVP  ) 
{

  glPointSize(4);
  Prim.Draw(PolygonMode, GL_PATCHES, MatrVP, rnd, cam);
  //Prim.Draw(PolygonMode, GL_POINTS, MatrVP, rnd, cam);

}

void tess::Response( void )
{

  //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex) * MAX_FLAKES, Flakes);
  //glBindBuffer(GL_ARRAY_BUFFER, 0);
}