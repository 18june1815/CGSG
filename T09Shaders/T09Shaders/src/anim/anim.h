#ifndef __ANIM_H_
#define __ANIM_H_

#include "rnd/rnd.h"


class anim;
class object
{
public:
  virtual void Draw( dlgl::matr MatrVP )
  {
  } /* End of 'Render' function */

  virtual void Response( void )
  {
  } /* End of 'Response' function */

  virtual void Keyboard( void )
  {
  } /* End of 'Keyboard' function */

  virtual void MouseWheel( void )
  {
  } /* End of 'MouseWheel' function */

  virtual void MouseMove( void )
  {
  } /* End of 'MouseMove' function */

}; /* End of 'object' class */


class anim
{
public:
  static const int MaxNumOfObjects = 100000;
  object *Objects[MaxNumOfObjects] {};
  int NumOfObjects = 0;


  anim( void )
  {
  }
  ~anim( void )
  {
    for (int i = 0; i < NumOfObjects; i++)
    {
      delete Objects[i];
    }       
    rnd.Close();
  }

  void Init( HWND hWnd, WPARAM wp, LPARAM lp )
  {
    rnd.Init( hWnd, wp, lp );
    SetScene();
  }
  void Resize( int W, int H)
  {
    rnd.Resize(W, H);
  }

  void CopyFrame( void )
  {
    rnd.CopyFrame();
  }
  void Draw( void )
  {
    for (int i = 0; i < NumOfObjects; i++)
    {
      Objects[i]->Response();
    }

    
    rnd.Start();
    rnd.cam.Draw(rnd.MatrView, rnd.MatrVP, rnd.MatrProj);
    for (int i = 0; i < NumOfObjects; i++)
      Objects[i]->Draw(rnd.MatrVP);
      
    static char buf[100];
    sprintf(buf, "T08OpenGL, FPS: %.5f", rnd.T.FPS);
    SetWindowText(rnd.hWnd, buf);
  }
  
  void MouseWheel( WPARAM wParam )
  {
    rnd.cam.MouseWheel(wParam);
    for (int i = 0; i < NumOfObjects; i++)
    {
      Objects[i]->MouseWheel();
    }
  }
  void MouseMove( WPARAM wParam, LPARAM lParam )
  {
    rnd.cam.MouseMove(wParam, lParam, rnd.FrameW, rnd.FrameH, rnd.MatrView);
    for (int i = 0; i < NumOfObjects; i++)
    {
      Objects[i]->MouseMove();
    }
  }


  anim & operator<<( object *Obj )
  {
    if (NumOfObjects < MaxNumOfObjects)
      Objects[NumOfObjects++] = Obj;
    return *this;
  } /* End of 'operator<<' function */

  void SetScene( void );
};
#endif /* __ANIM_H_ */