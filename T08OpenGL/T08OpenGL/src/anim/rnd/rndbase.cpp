#include "rnd.h"
      

void rnd::RenderInit( HWND hWnd, WPARAM wp )
{
  int i;
  UINT nums;
  PIXELFORMATDESCRIPTOR pfd = {0};

  rnd::hWnd = hWnd;

  hDC = GetDC(hWnd);
  wParam = wp;

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
  glClearColor(0.30, 0.47, 0.8, 1);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  ProjSize = 0.1;
  ProjDist = 0.1;
  ProjFarClip = 300;

  // Set MatrVP
  MatrVP = dlgl::matr::Identity();
  ProjSet();
 
  //Set timer
  SetTimer(hWnd, 30, 2, NULL);

   static char buf[100];
   sprintf(buf, "T08OpenGL, FPS: %.5f", T.FPS);
   SetWindowText(rnd::hWnd, buf);
                                                          
}

void rnd::RenderClose()
{
  //OpenGL deinit
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hGLRC);

  glFinish();
  ReleaseDC(hWnd, hDC); 
}
void rnd::RenderResize( int W, int H )
{  
  glViewport(0, 0, W, H);
  FrameW = W;
  FrameH = H;
  ProjSet();

  T.Response();
}

void rnd::RenderStart( void )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  T.Response();                  
  
}

void rnd::RenderCopyFrame( void )
{
  SwapBuffers(hDC);
}

void rnd::ProjSet( void )
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

void rnd::RenderMouseWheel( WPARAM wp )
{
  wParam = wp;
}

void rnd::RenderMouseMove( LPARAM lp )
{
  lParam = lp;
}

