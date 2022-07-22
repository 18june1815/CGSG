#ifndef __RND_H_
#define __RND_H_

#include "def.h"
#include "timer.h"

namespace rnd
{
  extern HWND hWnd;
  extern HDC hDC;
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
  void Init( HWND hWnd, WPARAM wp );
  void Resize( int W, int H );
  void CopyFrame( void );
  void Start( void );
  void Close( void );
  void MouseWheel( WPARAM wp );
  void MouseMove( LPARAM lp );
}


#endif /* __RND_H_ */