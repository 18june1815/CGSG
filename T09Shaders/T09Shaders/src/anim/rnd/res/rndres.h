#ifndef __RNDRES_H_
#define __RNDRES_H_ 

#include "def.h"

#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\wglew.h>

#define STR_MAX 300
#define MAX_SHADERS 30
#define MAX_TEXTURES 30
#define MAX_MATERIALS 300

class material
{
public:
  char Name[STR_MAX] = ""; // Material name

  // Illumination coefficients
  dlgl::vec3 Ka, Kd, Ks;  // Ambient, diffuse, specular coefficients
  float Ph;               // Phong power coefficient
  float Trans;            // Transparency factor
  int Tex[8];             // Texture references from texture table (or -1)
  int ShdNo;              // Shader number in shader table

  material ( void )
  {
  }
  
  static material DefMaterial( void );
};


struct texture
{
  char Name[STR_MAX]; // Texture name
  int W, H;        // Texture size in pixels
  GLuint TexId;      // OpenGl texture Id

  texture ( void )
  {
  }

};
                                       
class shader 
{
public:
  char Name[STR_MAX]; // Texture name
  int ProgId;         // Shader program Id
  const char *FileNamePrefix;

  shader( void )
  {
    ProgId = Load("default");
  }
  shader( const char *ShaderFileNamePrefix )
  {
    FileNamePrefix = ShaderFileNamePrefix;
    ProgId = Load(FileNamePrefix);
    strncpy(Name, FileNamePrefix, STR_MAX - 1);
  }

  char *LoadTextFromFile( const char *FileName );
  void Log( const char *Type, const char *Text  );
  int Load( const char *ShaderFileNamePrefix );
  void Delete( void );
  
  void Update( void );
};


class resources
{
public:
  shader *shd[MAX_SHADERS] {}; // Array of shaders
  int NumOfShaders = 0;                        

  texture *tex = new texture[MAX_TEXTURES];
  int NumOfTextures = 0;

  material mtl[MAX_MATERIALS] {};
  int NumOfMaterials = 0;

  int AddShader( const char *ShaderFileNamePrefix);
  void UpdateShader( void );

  int AddImg( const char *Name, int W, int H, int C, BYTE *Bits );
  int AddTexture( char *FileName );

  int AddMaterial( material *Mtl );
  int ApplyMaterial( int MtlNo );
  

  
  void Init( void );
  void Close( void ); 


};
#endif /* __RNDRES_H_ */