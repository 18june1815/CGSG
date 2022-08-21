#include "anim.h"
#include "prim.h"
#include "rnd/camera.h"
#include "Globe.h"

namespace rnd
{
  void anim::SetScene( void )
  {
    *this << new camera();
    *this << new prim("bin/models/cow.obj");
    
    //for (int i = 0; i < 10; i++ )
      //*this << new globe();
  }
}
