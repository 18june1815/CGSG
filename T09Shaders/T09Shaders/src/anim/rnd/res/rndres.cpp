#include "anim/rnd/rnd.h"
#include "rndres.h"

void Res::Init( void )
{
  shd.ProgId = shd.Load("default");
}

void Res::Close( void )
{
  shd.Delete(shd.ProgId);
}