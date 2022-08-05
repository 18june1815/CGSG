#include <windows.h>
#include "rnd.h"

namespace rnd
{
  HWND hWnd;
  HDC hDC;
  HGLRC hGLRC;
  int FrameW, FrameH;
  HFONT hFnt;
  PAINTSTRUCT ps;
  WPARAM wParam;
  LPARAM lParam;
  

  dlgl::matr 
    MatrView,  // View coordinate system matrix
    MatrProj,  // Projection coordinate system matrix
    MatrVP; 

  double 
    ProjSize = 0.1,
    ProjDist = 0.1,
    ProjFarClip = 300;

  timer T;
}
