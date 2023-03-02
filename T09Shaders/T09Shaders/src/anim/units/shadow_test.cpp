#include "Units.h"
#define SIZE 256


shadow_test::shadow_test( render *R, camera *c,  std::vector<object *> Obj )
{
  name = "shadow_test";
  rnd = R;
  cam = c;

  Objects = Obj;
  material m = material::DefMaterial();
  m.Name = "shadow_test";

  m.Tex[0] = rnd->resources.TexAddFmt("shadowMap", SIZE, SIZE, GL_DEPTH_COMPONENT24); 
  m.ShdNo = rnd->resources.AddShader("shadow_test") - 1;


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


void shadow_test::Delete( void )
{
  //Remove FBO
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDeleteFramebuffers(1, &FBO);

  Prim.Delete();
}
void shadow_test::Draw( dlgl::matr MatrVP  ) 
{
  Prim.Draw(PolygonMode, GL_POINTS, dlgl::matr::Identity(), rnd, cam);

}

void shadow_test::Response( dlgl::matr MatrVP )
{
  float clear_depth = 1;
  dlgl::vec3 CamLoc = cam->Loc, CamAt = cam->At;

  cam->Loc = {2, 10, 2};
  cam->At = {0, 5, 0};
 
  glViewport(0, 0, SIZE, SIZE);
  rnd->MatrProj = dlgl::matr::Ortho(-SIZE / 2., SIZE / 2., -SIZE / 2., SIZE/ 2.,
                                  rnd->ProjDist, rnd->ProjFarClip);
  cam->Draw(rnd->MatrView, rnd->MatrVP, rnd->MatrProj);

  rnd->ShadowMatr = dlgl::matr::Scale({SIZE,SIZE,SIZE}) * rnd->MatrVP ;
  
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);
 
  glClearBufferfv(GL_DEPTH, 0, &clear_depth);

  Objects[2]->Draw(rnd->MatrVP);
  glFinish();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, rnd->FrameW, rnd->FrameH);
  
  cam->Loc = CamLoc;
  cam->At = CamAt;
  rnd->ProjSet();
  cam->Draw(rnd->MatrView, rnd->MatrVP, rnd->MatrProj);

}