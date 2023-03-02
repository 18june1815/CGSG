#ifndef __RNDRES_H_
#define __RNDRES_H_ 

#include "def.h"
#include <string>


#define STR_MAX 300
#define MAX_SHADERS 300
#define MAX_TEXTURES 300
#define MAX_MATERIALS 300

class material
{
public:
  std::string Name;
  // Illumination coefficients
  dlgl::vec3 Ka, Kd, Ks;  // Ambient, diffuse, specular coefficients
  float Ph;               // Phong power coefficient
  float Trans;            // Transparency factor
  int Tex[8];             // Texture references from texture table (or -1)
  int ShdNo;              // Shader number in shader table

  material ( void )
  {
    Name = "Default";
    Ka = dlgl::vec3(0.1, 0.1, 0.1);
    Kd = dlgl::vec3(0.9, 0.9, 0.9);
    Ks = dlgl::vec3(0.3, 0.3, 0.3);
    Ph = 30;
    Trans = 0;
    ShdNo = 0;
    for (int i = 0; i < 8; i++)
      Tex[i] = -1; 
  }
  static material DefMaterial( void );
  static material GetLibMaterial( std::string mtlName );
};


struct texture
{
  std::string Name;
  int W, H;        // Texture size in pixels
  GLuint TexId;      // OpenGl texture Id
};

class shader
{
public:
  char Name[STR_MAX]; // Shader name
  int ProgId;         // Shader program Id

  shader( void )
  {
    strncpy(Name, "default", STR_MAX - 1);
    ProgId = 0;
  }
  shader( const char *ShaderFileNamePrefix )
  {
    strncpy(Name, ShaderFileNamePrefix, STR_MAX - 1);
    ProgId = 0;
    ProgId = Load();
  }

  std::string LoadTextFromFile( const char *FileName );
  void Log( const char *Type, const char *Text  );
  int Load( void );
  void Delete( void );
};



class resources
{
public:
  shader shd[MAX_SHADERS] {}; // Array of shaders
  int NumOfShaders = 0;                        

  texture tex[MAX_TEXTURES] {};
  int NumOfTextures = 0;

  material mtl[MAX_MATERIALS] {};
  int NumOfMaterials = 0;

  int AddShader( const char *ShaderFileNamePrefix);
  void UpdateShader( void );

  int AddImg( std::string Name, int W, int H, int C, BYTE *Bits );
  void AddTexture( material *Mtl, std::string TexName, const char *TexFile );
  int AddTextureFromFile( material *Mtl, std::string TexName, const char *FileName );
  int TexAddFmt( std::string Name, int W, int H, int GLType);
  int FindTexture( std::string name );

  int AddMaterial( material *Mtl );
  int ApplyMaterial( int MtlNo, UINT64 Time );
  int FindMaterial( std::string name );
  
  bool LoadFont( const char *FileName );
  void PrintText( char *Str, dlgl::vec3 Pos, float Size, UINT64 Time );

  void Init( void );
  void Close( void ); 
};
#endif /* __RNDRES_H_ */