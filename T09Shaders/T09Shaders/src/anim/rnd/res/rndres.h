#ifndef __RNDRES_H_
#define __RNDRES_H_ 

#include "def.h"

#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\wglew.h>

#define STR_MAX 300
#define MAX_SHADERS 30
#define MAX_TEXTURES 30

class ResObject
{
public:
  virtual void Init( void );
  virtual void Close( void );
  virtual void Update( void );
}; /* End of 'object' class */


class texture
{
  char Name[STR_MAX]; // Texture name
  int W, H;        // Texture size in pixels
  UINT TexId;      // OpenGl texture Id
  void Init( void );
  void Close( void );
  int AddImg( char *Name, int W, int H, int C, void *Bits );
};
                                       
class shader : public ResObject
{
public:
  char Name[STR_MAX]; // Shader filename prefix
  int ProgId;         // Shader program Id

  shader( void )
  {
    Load("default");
  }
  shader( const char *ShaderFileNamePrefix )
  {
    Load(ShaderFileNamePrefix);
  }

  void Init( void ) override;
  void Close( void ) override;
  static char *LoadTextFromFile( const char *FileName );
  static void Log( const char *ShaderName, const char *Prefix, const char *Type, const char *Text );
  int Load( const char *ShaderFileNamePrefix );
  void Delete( int ProgId );
  
  void Update( void );
};


class Res
{
public:
  int ShadersSize;         // Shaders array store size
  shader shd[MAX_SHADERS]; // Array of shaders

  static const int MaxNumOfObjects = 100000;
  ResObject *Objects[MaxNumOfObjects] {};
  int NumOfObjects = 0;
    
  void Init( void );
  void Close( void );
  int AddShader( const char *ShaderFileNamePrefix);

  Res & operator<<( ResObject *Obj )
  {
    if (NumOfObjects < MaxNumOfObjects)
      Objects[NumOfObjects++] = Obj;
    return *this;
  } /* End of 'operator<<' function */


};
#endif /* __RNDRES_H_ */