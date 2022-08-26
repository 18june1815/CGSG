#include "anim/rnd/rnd.h"
#include "rndres.h"

void Res::Init( void )
{
  *this << new shader();
}

void Res::Close( void )
{
  for (int i = 0; i < NumOfObjects; i++)
  {
    Objects[i]->Close();
    delete Objects[i];
  }       
}

int Res::AddShader( const char *ShaderFileNamePrefix)
{
  *this << new shader(ShaderFileNamePrefix);
}
