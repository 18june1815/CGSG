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

//extern render rnd;

class render 
{
public:
  HDC hDC;
  HWND hWnd;
  HGLRC hGLRC; //OpenGL rendering context
 
  resources resources;
  timer T;
 
  int FrameW = 300, FrameH = 400;

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
    //Init();
  }
  ~render( void )
  {
    ReleaseDC(hWnd, hDC); 
  }

  void Init( HWND hWnd );
  void Close( void );
  void Start( void );
  void Resize ( int W, int H );
  void CopyFrame( void );
  void ProjSet( void );
 
};

#endif /* __RENDER_H_ */