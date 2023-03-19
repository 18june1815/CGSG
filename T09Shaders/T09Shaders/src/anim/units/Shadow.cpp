#include "Units.h"
#define SHADOW_MAP_SIZE 2048


shadow::shadow( render *R, camera *c,  std::vector<object *> Obj )
{
  name = "shadow";
  rnd = R;
  cam = c;

  Objects = Obj;
  material m = material::DefMaterial();
  m.Name = "shadow";

  m.Tex[0] = rnd->resources.TexAddFmt("shadowMap", SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, GL_DEPTH_COMPONENT24); 
  m.ShdNo = rnd->resources.AddShader("shadow") - 1;


  Prim.Create(NULL, 1, NULL, 0);
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;    

  // Create shadow FBO
  glGenFramebuffers(1, &FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);

  //Attach depth texture
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, rnd->resources.tex[m.Tex[0]].TexId, 0);

  int w, h, fmt;
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &fmt);

  int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE)
    int a = 1;

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  for (int i = 0; i < rnd->resources.NumOfMaterials; i++)
  {
    material *mtl = &(rnd->resources.mtl[i]);
    mtl->Tex[1] = m.Tex[0];
  }
}


void shadow::Delete( void )
{
  //Remove FBO
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDeleteFramebuffers(1, &FBO);

  Prim.Delete();
}
void shadow::Draw( dlgl::matr MatrVP  ) 
{
  Prim.Draw(PolygonMode, GL_POINTS, dlgl::matr::Identity(), rnd, cam);

}

void shadow::Response( dlgl::matr MatrVP )
{
  float size = 30, clear_depth = 1;
  dlgl::vec3 CamLoc = cam->Loc, CamAt = cam->At;

  cam->Loc = {2, 5, 2};
  cam->At = {0, 0, 0};
 
  glViewport(0, 0, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
  rnd->MatrProj = dlgl::matr::Ortho(-size / 2., size / 2., -size / 2., size / 2.,
                                  -size, size * 10);
  cam->Draw(rnd->MatrView, rnd->MatrVP, rnd->MatrProj);

  rnd->ShadowMatr = rnd->MatrVP ;
  
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);
 
  glClearBufferfv(GL_DEPTH, 0, &clear_depth);

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(4, 4);

  Objects[2]->Draw(rnd->MatrVP);
  glFinish();
  glDisable(GL_POLYGON_OFFSET_FILL);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, rnd->FrameW, rnd->FrameH);
  
  cam->Loc = CamLoc;
  cam->At = CamAt;
  rnd->ProjSet();
  cam->Draw(rnd->MatrView, rnd->MatrVP, rnd->MatrProj);

}