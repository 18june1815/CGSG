#ifndef __RENDER_H_
#define __RENDER_H_

#include <Windows.h>

#include "def.h"
#include "anim/rnd/timer.h"
#include "res/rndres.h"
#include "rndtgrt.h"
  
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
class render;

//extern render rnd;

class render 
{
public:
  HDC hDC;
  HWND hWnd;
  HGLRC hGLRC; //OpenGL rendering context
 
  res *resources;
  tgrt targets;
  timer T;
 
  int FrameW = 300, FrameH = 400;

  dlgl::matr 
    MatrView,  // View coordinate system matrix
    MatrProj,  // Projection coordinate system matrix
    MatrVP,
    ShadowMatr; 

  double 
    ProjSize = 0.1,
    ProjDist = 0.1,
    ProjFarClip = 300;

  render( void )
  {
    //Init();
  }
  ~render( void )
  {
    ReleaseDC(hWnd, hDC); 
  }

  void Init( HWND hWnd );
  void Close( void );
  void Start( void );
  void End( void );
  void Resize ( int W, int H );
  void CopyFrame( void );
  void ProjSet( void );
  void ProjSetOrtho( void );
 
};

#endif /* __RENDER_H_ */