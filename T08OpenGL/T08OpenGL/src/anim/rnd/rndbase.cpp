#include "rnd.h"
      

//rnd::anim MyAnim;
void rnd::Init( HWND hWnd, WPARAM wp )
{
  rnd::hWnd = hWnd;
  wParam = wp;

  MatrVP = dlgl::matr::Identity();
  ProjSet();
 
  // Render parameter setup
  ProjSize = 0.1;
  ProjDist = 0.1;
  ProjFarClip = 300;

  //Set timer
  SetTimer(hWnd, 30, 2, NULL);
}

void rnd::Close()
{
  ReleaseDC(hWnd, hDC); 
}
void rnd::Resize( int W, int H )
{  
  FrameW = W;
  FrameH = H;
  ProjSet();

  T.Response();
}

void rnd::Start( void )
{
  T.Response();
}

void rnd::CopyFrame( void )
{
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

void rnd::MouseWheel( WPARAM wp )
{
  wParam = wp;
}

void rnd::MouseMove( LPARAM lp )
{
  lParam = lp;
}

