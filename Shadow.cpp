#include "Units.h"
#define SIZE 256

Shadow::Shadow( render *Rnd, camera *c )
{
  name = "Shadow";
  cam = c;
  rnd = Rnd;
  material m = material::DefMaterial();
  m.Name = "shadow";
  //m.Tex[0] = rnd->resources.TexAddFmt("shadowMap", SIZE, SIZE, GL_DEPTH_COMPONENT24); 
  m.Tex[0] = rnd->resources.AddTextureFromFile(&m, "grass", "bin/textures/plant.g32");
  m.ShdNo = rnd->resources.AddShader("shadow_test ") - 1;
                                                            
  Prim.Create(NULL, 1, NULL, 0);
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;    
  
  /*
  // Create shadow FBO
  glGenFramebuffers(1, &FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);

  //Attach depth texture
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, rnd->resources.tex[m.Tex[0]].TexId,
    rnd->resources.tex[m.Tex[0]].TexId);

  
  int w, h, fmt;
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &fmt);

  int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  //if (status != GL_FRAMEBUFFER_COMPLETE)
    //OutputDebugStr("Error in framebuffer\n");
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
    */
}

void Shadow::Delete( void )
{
  //Remove FBO
  //glBindFramebuffer(GL_FRAMEBUFFER, FBO);
  //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
  //glBindFramebuffer(GL_FRAMEBUFFER, 0);
  //glDeleteFramebuffers(1, &FBO);

  Prim.Delete();
}

void Shadow::Draw( dlgl::matr MatrVP )
{
  dlgl::matr
  Proj = dlgl::matr::Ortho(-rnd->FrameW / 2, rnd->FrameW / 2 , -rnd->FrameH / 2, rnd->FrameH / 2,-1, 1),
  World = dlgl::matr::RotateY(30),
  View = dlgl::matr::Identity(),
  Matr_VP = View * Proj;
  

  Prim.Draw(PolygonMode, GL_POINTS, MatrVP, rnd, cam);
  //dlgl::matr M = dlgl::matr::Translate({0.7, 0, 0});
  //Prim.Draw(PolygonMode, GL_TRIANGLE_STRIP, M * MatrVP, rnd, cam);
}

