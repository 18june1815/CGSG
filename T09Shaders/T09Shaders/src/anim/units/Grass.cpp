#include "Units.h"

grass::grass( render *R, camera *c )
{
  name = "grass";
  rnd = R;
  cam = c;

  material m = material::DefMaterial();
  m.Name = "grass";
  m.Tex[0] = rnd->resources.AddTextureFromFile(&m, "grass", "bin/textures/plant.g32");
  m.Tex[1] = rnd->resources.AddTextureFromFile(&m, "Mounts", "bin/textures/hf.bmp");
  m.ShdNo = rnd->resources.AddShader("grass") - 1;


  Prim.Create(NULL, 100, NULL, 0);
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;    
}


void grass::Draw( dlgl::matr MatrVP  ) 
{

  Prim.Draw(PolygonMode, GL_POINTS, MatrVP, rnd, cam);

}

void grass::Response( void )
{

  //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex) * MAX_FLAKES, Flakes);
  //glBindBuffer(GL_ARRAY_BUFFER, 0);
}                          