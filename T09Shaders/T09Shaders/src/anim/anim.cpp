#include "anim.h"
#include "prim.h"
#include "Globe.h"
#include "ObjPrim.h"


void anim::SetScene( void )
{
  *this << new objprim("bin/models/cow.obj");
  for (int i = 0; i < 5; i++ )
    *this << new globe();

}

