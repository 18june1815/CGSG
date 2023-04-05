#include "rnd.h"


void render::Init( HWND hWnd )
{
  int i;
  UINT nums;
  PIXELFORMATDESCRIPTOR pfd = {0};

  hWnd = hWnd;

  hDC = GetDC(hWnd);
   
  //OpenGL init: pixel format setup
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(hDC, &pfd);
  DescribePixelFormat(hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(hDC, i, &pfd);

  //OpenGL init: rendering context setup
  hGLRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hGLRC);

  //GLEW librrary init
  if(glewInit() != GLEW_OK)
  {
    MessageBox(hWnd, "Error OpenGL initialization", "ERROR", MB_OK | MB_ICONERROR);
      exit(0);
  }

  //Enable a new OpenGL profile support
  HGLRC hRC;
  int PixelAttribs[] = 
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  int ContextAttribs[] = 
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
    0
  };
  wglChoosePixelFormatARB(hDC, PixelAttribs, NULL, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(hDC, NULL, ContextAttribs);

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hGLRC);

  hGLRC = hRC;
  wglMakeCurrent(hDC, hGLRC);

  wglSwapIntervalEXT(1);

  // Render parameter setup
  glClearColor(0.30f, 0.47f, 0.8f, 1.f);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);

  glEnable(GL_BLEND);
  //glBlendFunc(GL_ONE, GL_ZERO);         

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  ProjSize = 0.1;
  ProjDist = 0.1;
  ProjFarClip = 300;

  // Set MatrVP
  MatrVP = dlgl::matr::Identity();
  ShadowMatr = dlgl::matr::Identity();
  ProjSet();

  SetTimer(hWnd, 30, 2, NULL);
  resources = new res;
  resources->Init();
  targets.Init(resources, FrameW, FrameH);
}

void render::Close( void )
{
  resources->Close();
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hGLRC);

  glFinish();
  targets.Close();
  delete resources;
  ReleaseDC(hWnd, hDC); 
}

void render::Start( void )
{
  T.Response();

  static double ReloadTime = 0;
  if (T.GlobalTime - ReloadTime > 6)
  {
    ReloadTime = T.GlobalTime;
    resources->UpdateShader();
  }

  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  targets.Start();
}

void render::End( dlgl::vec3 CamLoc )
{
  glFinish(); 
  targets.End(T.Time, CamLoc);
}

void render::Resize ( int W, int H )
{
  glViewport(0, 0, W, H);
  FrameW = W;
  FrameH = H;
  ProjSet();
  T.Response();
  targets.Resize(W, H);
}              

void render::CopyFrame( void )
{
  SwapBuffers(hDC);
}

void render::ProjSet( void )
{
  double rx, ry;
  rx = ry = ProjSize;
  
  /* Correct aspect ratio */
  if (FrameW > FrameH)
    rx *= (double)FrameW / FrameH;
  else
    ry *= (double)FrameH / FrameW;
  
  MatrProj = dlgl::matr::Frustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
                                  ProjDist, ProjFarClip);
  MatrVP = MatrView * MatrProj;
}


void render::ProjSetOrtho( void )
{
  double rx, ry;
  rx = ry = ProjSize;
  
  /* Correct aspect ratio */
  if (FrameW > FrameH)
    rx *= (double)FrameW / FrameH;
  else
    ry *= (double)FrameH / FrameW;
  
  MatrProj = dlgl::matr::Ortho(-rx / 2, rx / 2, -ry / 2, ry / 2,
                                  ProjDist, ProjFarClip);
  MatrVP = MatrView * MatrProj;
}

