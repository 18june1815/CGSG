#ifndef __RENDER_H_
#define __RENDER_H_

#include <Windows.h>

#include "def.h"
#include "anim/rnd/timer.h"
#include "res/rndres.h"
#include "camera.h"
  
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
class render;

extern render rnd;

class render 
{
public:
  HDC hDC;
  HWND hWnd;
  HGLRC hGLRC; //OpenGL rendering context
  WPARAM wParam;
  LPARAM lParam;
  resources resources;
  timer T;
 
  int FrameW, FrameH;

  dlgl::matr 
    MatrView,  // View coordinate system matrix
    MatrProj,  // Projection coordinate system matrix
    MatrVP; 

  double 
    ProjSize = 0.1,
    ProjDist = 0.1,
    ProjFarClip = 300;

    camera cam;
  render( void )
  {
  }
  ~render( void )
  {
      ReleaseDC(hWnd, hDC); 
  }

  void Init( HWND hwnd, WPARAM wp, LPARAM lp );
  void Close( void );
  void Start( void );
  void Resize ( int W, int H );
  void CopyFrame( void );
  void ProjSet( void );
 
};

#endif /* __RENDER_H_ */