#ifndef __RND_H_
#define __RND_H_

#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\wglew.h>
#include <GL\wglext.h>
#include <GL\freeglut.h>

#include "def.h"
#include "timer.h"


namespace rnd
{
  extern HWND hWnd;
  extern HDC hDC;      
  extern HGLRC hGLRC; //OpenGL rendering context
  extern int FrameW, FrameH;
  extern HFONT hFnt;
  extern PAINTSTRUCT ps;
  extern WPARAM wParam;
  extern LPARAM lParam;

  extern timer T;
  
  extern double 
    ProjSize,
    ProjDist,
    ProjFarClip;
  extern dlgl::matr
    MatrView,  // View coordinate system matrix
    MatrProj,  // Projection coordinate system matrix
    MatrVP;    // Stored (View * Proj) matrix

  //extern dlgl::vec3 CameraLoc; // Location of the camera

  
  // Cache primitive projaction points
  extern POINT *StoredProjPoints;
  extern INT StoredProjPointsSize;
    
  void ProjSet( void );
  void RenderInit( HWND hWnd, WPARAM wp );
  void RenderResize( int W, int H );
  void RenderCopyFrame( void );
  void RenderStart( void );
  void RenderClose( void );
  void RenderMouseWheel( WPARAM wp );
  void RenderMouseMove( LPARAM lp );
}


#endif /* __RND_H_ */