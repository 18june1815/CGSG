#ifndef __INPUT_H_
#define __INPUT_H_

#include "def.h"
class input
{
public:
  BYTE Keys[256];
  BYTE KeysOld[256];
  BYTE KeysClick[256]; 

  int Mx, My, Mz, Mdx, Mdy, Mdz;
  int MouseWheel;

  input( void )
  {
    MouseWheel = 0;
    Mdx = Mdy = Mdz = 0;
    KbdResponse();
    MouseClickResponse();
  }

  void KbdResponse( void )
  {
    (void)GetKeyboardState(Keys);
    for (int i = 0; i < 256; i++)
    {
      Keys[i] >>= 7;
      KeysClick[i] = Keys[i] && !KeysOld[i];
    }
    memcpy(KeysOld, Keys, 256);
  }

  void MouseClickResponse( void )
  {
    POINT pt;
    GetCursorPos(&pt);

    Mdx = pt.x - Mx;
    Mdy = pt.y - My;

    Mx = pt.x;
    My = pt.y;
  }

  void MouseWResponse( WPARAM wParam )
  {
    MouseWheel += (SHORT)HIWORD(wParam);

    Mdz = MouseWheel;
    Mz += MouseWheel;
  }
};

#endif // __INPUT_H_

