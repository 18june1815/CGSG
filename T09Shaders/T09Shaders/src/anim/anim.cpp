#include "anim.h"
#include "prim.h"
#include "Globe.h"


void anim::SetScene( void )
{
  *this << new prim("bin/models/cow.obj");
  for (int i = 0; i < 10; i++ )
    *this << new globe();

}

