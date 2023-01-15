#include "Units.h"

snow::snow( render *R, camera *c )
{
  name = "snow";
  rnd = R;
  cam = c;
  int Ind[MAX_FLAKES];
  material m = material::DefMaterial();

  //Fill snowflakes
  for (int i = 0; i < MAX_FLAKES; i++)
  {
  
    Flakes[i].P = dlgl::vec3((float) rand()/RAND_MAX * 100. - 50.,
                             (float) rand()/RAND_MAX * 100., 
                             (float) rand()/RAND_MAX * 100. - 50.);
    Ind[i] = i; 
   }
  m.Name = "snow";
  m.Tex[0] = rnd->resources.AddTextureFromFile(&m, "snow", "bin/textures/snow.g32");
  m.ShdNo = rnd->resources.AddShader("snow") - 1;

  Prim.Create(Flakes, MAX_FLAKES, Ind, MAX_FLAKES);
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
}


void snow::Draw( dlgl::matr MatrVP  ) 
{
  glPointSize(3);
  Prim.Draw(PolygonMode, GL_POINTS, MatrVP, rnd, cam);
}

void snow::Response( void )
{
  // Move snowflakes
  for (int i = 0; i < MAX_FLAKES; i++)
  {
    Flakes[i].P.Y -= rnd->T.DeltaTime;
    if(Flakes[i].P.Y <= 0)
      Flakes[i].P.Y += 10;
  }
  glBindBuffer(GL_ARRAY_BUFFER, Prim.VBuf);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex) * MAX_FLAKES, Flakes);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}