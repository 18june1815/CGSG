#include "Units.h"

CollisionFire::CollisionFire( render *R, camera *c )
{
  name = "CollisionFire";
  rnd = R;
  cam = c;
  int Ind[1] = {0};

  Loc[0].P = dlgl::vec3(1.,1.,1.);
  material m = material::DefMaterial();
  m.Name = "fire";
  m.Tex[0] = rnd->resources.AddTextureFromFile(&m, "smoke", "bin/textures/SMOKE.G32");
  m.ShdNo = rnd->resources.AddShader("fire") - 1;
 
  Prim.Create(Loc, 1, Ind, 1);
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
}

void CollisionFire::Draw( dlgl::matr MatrVP  ) 
{
    
  int loc, ProgId;

  // Pass render uniforms
  ProgId = rnd->resources.ApplyMaterial(Prim.MtlNo, rnd->T.Time);  
   
  if ((loc = glGetUniformLocation(ProgId, "IsFire")) != -1)
    glUniform1f(loc, IsFire);

  glDepthMask(false);
  Prim.Draw(PolygonMode, GL_POINTS, MatrVP, rnd, cam);
  glDepthMask(true);

}
                                    
void CollisionFire::Response( void )
{
  glBindBuffer(GL_ARRAY_BUFFER, Prim.VBuf);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex) * 1, Loc);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}