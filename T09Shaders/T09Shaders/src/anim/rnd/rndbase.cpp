#include "rnd.h"

void render::Init( HWND hwnd, WPARAM wp, LPARAM lp )
{
  int i;
  UINT nums;
  PIXELFORMATDESCRIPTOR pfd = {0};

  hWnd = hwnd;
  wParam = wp;
  lParam = lp;

  hDC = GetDC(hWnd);
   
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
  if(glewInit() != GLEW_OK  ||
    !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    MessageBox(hWnd, "Error OpenGL initialization", "ERROR", MB_OK | MB_ICONERROR);
      exit(0);
  }

  //Enable a new OpenGL profile support
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

  ProjSize = 0.1;
  ProjDist = 0.1;
  ProjFarClip = 300;

  // Set MatrVP
  MatrVP = dlgl::matr::Identity();
  ProjSet();

  SetTimer(hWnd, 30, 2, NULL);
  res.Init();
}

void render::Close( void )
{
  res.Close();
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hGLRC);

  glFinish();
  ReleaseDC(hWnd, hDC); 

}

void render::Start( void )
{
  static double ReloadTime = 0;

  T.Response();
  if (T.GlobalTime - ReloadTime > 3)
  {
    ReloadTime = T.GlobalTime;
    res.shd.Delete(res.shd.ProgId);
    res.shd.ProgId = res.shd.Load("default");
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render::Resize ( int W, int H )
{
  glViewport(0, 0, W, H);
  FrameW = W;
  FrameH = H;
  ProjSet();
  T.Response();
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

