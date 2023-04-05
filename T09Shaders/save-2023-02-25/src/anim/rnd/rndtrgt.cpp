#include "rndtgrt.h"

void tgrt::Init( res *r, int w, int h )
{
  resources = r;

  char Name[] = "target0";
  for (int i = 0; i < N_TARGETS; i++)
  {
    Name[6] = '0' + i;
    TargetTexId[i] = resources->TexAddFmt(Name, W, H, GL_RGBA32F); 
  }
  TargetShd = resources->AddShader("target0") - 1;
  
  W = w;
  H = h;
  Create();
}

void tgrt::Resize( int w, int h )
{
  Free();
  W = w;
  H = h;
  Create();
  glViewport(0, 0, W, H);
}

void tgrt::Create()
{
  GLuint DrawBuffers[N_TARGETS];
  
  /* Create FBO */
  glGenFramebuffers(1, &TargetFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, TargetFBO);
 
  /* Attach textures */
  for (int i = 0; i < N_TARGETS; i++)
  {
    /* Resize target texture */
    glDeleteTextures(1, &TargetTexId[i]);
    glGenTextures(1, &TargetTexId[i]);
    glBindTexture(GL_TEXTURE_2D, TargetTexId[i]);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, W, H);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
 
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, TargetTexId[i], 0);
    DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
  }
  glDrawBuffers(N_TARGETS, DrawBuffers);
 
  /* Attach render buffer (depth) */
  glGenRenderbuffers(1, &TargetRndBuf);
  glBindRenderbuffer(GL_RENDERBUFFER, TargetRndBuf);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, W, H);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, TargetRndBuf);
 
  int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE)
    int a = 1;

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void tgrt::Free( void )
{
  glBindFramebuffer(GL_FRAMEBUFFER, TargetFBO);
  /* Detach textures */
  for (int i = 0; i < N_TARGETS; i++)
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, 0, 0);
  
  /* Detach render buffer (depth) */
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
  glDeleteRenderbuffers(1, &TargetRndBuf);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDeleteFramebuffers(1, &TargetFBO);
  TargetFBO = 0;
  TargetRndBuf = 0;
}


void tgrt::Close()
{
  Free();
}           


void tgrt::Start()
{
  float col[4] = {0, 1, 0, 1}, depth = 1;
 
  glBindFramebuffer(GL_FRAMEBUFFER, TargetFBO);
  for (int i = 0; i < N_TARGETS; i++)
    glClearBufferfv(GL_COLOR, i, col);
  glClearBufferfv(GL_DEPTH, 0, &depth);
  glViewport(0, 0, W, H);
}

void tgrt::End()
{
  glFinish();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
   
  float col[4] = {0, 1, 0, 1}, depth = 1;
  glClearBufferfv(GL_COLOR, 0, col);
  glClearBufferfv(GL_DEPTH, 0, &depth);

  glViewport(0, 0, W, H);
  glDisable(GL_DEPTH_TEST);

  glUseProgram(resources->shd[TargetShd].ProgId);
  for (int i = 0; i < N_TARGETS; i++)
  {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, TargetTexId[i]);
  }

  glDrawArrays(GL_POINTS, 0, 1);

  
  glEnable(GL_DEPTH_TEST);
  glFinish();
}