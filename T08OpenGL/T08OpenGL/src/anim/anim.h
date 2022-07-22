#ifndef __RNDANIM_H_
#define __RNDANIM_H_
#include "rnd/rnd.h"


namespace rnd
{
  class anim;
  class object
  {
  public:
    virtual void Render( void )
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
      Close();
    }
 
    void Init( HWND hWnd, WPARAM wp )
    {  
      Init(hWnd, wp);
      SetScene();
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
      Start();
      for (int i = 0; i < NumOfObjects; i++)
      {
        Objects[i]->Render();
      }
    }

    void Resize( int W, int H )
    {
      Resize(W, H);
    }
    void MouseWheel( void )
    {
      for (int i = 0; i < NumOfObjects; i++)
      {
        Objects[i]->MouseWheel();
      }
    }

    void MouseMove( void )
    {
      for (int i = 0; i < NumOfObjects; i++)
      {
        Objects[i]->MouseMove();
      }
    }

    void SetScene( void );
  };
}


#endif /* __RNDANIM_H_ */
    