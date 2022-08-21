#ifndef __RNDANIM_H_
#define __RNDANIM_H_
#include "rnd/rnd.h"


namespace rnd
{
  class anim;
  class object
  {
  public:
    virtual void Draw( void )
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
      RenderClose();
    }
 
    void Init( HWND hWnd, WPARAM wp )
    {  
      RenderInit(hWnd, wp);
      SetScene();
    }

    void CopyFrame( void )
    {
      RenderCopyFrame();
    }

    anim & operator<<( object *Obj )
    {
      if (NumOfObjects < MaxNumOfObjects)
        Objects[NumOfObjects++] = Obj;
      return *this;
    } /* End of 'operator<<' function */

    void Render( void )
    {

      for (int i = 0; i < NumOfObjects; i++)
      {
        Objects[i]->Response();
      }
     
      RenderStart();
      for (int i = 0; i < NumOfObjects; i++)
      {
        Objects[i]->Draw();
      }
     
      static char buf[100];
      sprintf(buf, "T08OpenGL, FPS: %.5f", T.FPS);
      SetWindowText(rnd::hWnd, buf);
     
    }

    void Resize( int W, int H )
    {
      RenderResize(W, H);

    }
    void MouseWheel( WPARAM wp )
    {
      RenderMouseWheel(wp);
      for (int i = 0; i < NumOfObjects; i++)
      {
        Objects[i]->MouseWheel();
      }
    }
    void MouseMove( LPARAM lp )
    {
      RenderMouseMove(lp);
      for (int i = 0; i < NumOfObjects; i++)
      {
        Objects[i]->MouseMove();
      }
    }

    void SetScene( void );
  };
}


#endif /* __RNDANIM_H_ */
    