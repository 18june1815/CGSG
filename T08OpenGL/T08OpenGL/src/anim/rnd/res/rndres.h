#ifndef __RNDRES_H_
#define __RNDRES_H_ 

#include "def.h"

#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\wglew.h>

class shader
{
public:
  int ProgId;
  shader( void )
  {
  }

  static char *LoadTextFromFile( const char *FileName );
  static void Log( const char *Prefix, const char *Type, const char *Text );
  int Load( const char *ShaderFileNamePrefix );
  void Delete( int ProgId );
};

class Res
{
public:
  shader shd;
  void Init( void );
  void Close( void );
};
#endif /* __RNDRES_H_ */