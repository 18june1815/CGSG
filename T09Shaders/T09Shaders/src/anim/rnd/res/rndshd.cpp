#include <fstream>

#include "def.h"
//#include "../rnd.h"
#include "rndres.h"


std::string shader::LoadTextFromFile( const char *FileName )
{
  std::ifstream f(FileName);
  if (!f)
    return "";
  f.seekg(0, std::fstream::end);
  std::fpos_t flen = f.tellg();
  f.seekg(0);

  std::string s(flen, ' ');
  f.read(s.data(), flen);
  return s;
}

void shader::Log( const char *Type, const char *Text  )
{
  FILE *F;

  if ((F = fopen("bin/shaders/Shader.LOG", "a")) == NULL)
    return;
  fprintf(F, "%s/%s.GLSL: \n%s\n", Name, Type, Text);
  fclose(F);
}

int shader::Load( void )
{
  char ErrText[200], TypeName[20];
  
  struct
  {
    const char *Name; //Shader file suffix name
    int Type;   //Shader OpenGL type
    int Id;     //Shader Id created by OpenGL
  } shd[] =
  {
    {"vert", GL_VERTEX_SHADER},
    {"frag", GL_FRAGMENT_SHADER}
  };
  int i, prg = 0, resources, Ns = sizeof(shd) / sizeof(shd[0]);
  bool is_ok = true;
  static char Buf[3000];

  for(i = 0; is_ok && i < Ns; i++)
  {
    //Load shader text from file
    sprintf(Buf, "bin/shaders/%s/%s.glsl", Name, shd[i].Name);
    std::string txt = LoadTextFromFile(Buf);
    if (txt.length() == 0)
    {
      sprintf(ErrText, "Error load file");
      Log(shd[i].Name, ErrText);
      is_ok = false;
      break;
    }
    //Create shader
    if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
    {
      sprintf(ErrText, "Error create shader");
      Log(shd[i].Name, ErrText);
      is_ok = false;
      break;
    }
    //Attach shader source code to shader
    const char *txt_ref = txt.c_str();
    glShaderSource(shd[i].Id, 1, &txt_ref, NULL);

    //Compile shader
    glCompileShader(shd[i].Id);
    glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &resources);
    if (resources != 1)
    {
      glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &resources, Buf);
      Log(shd[i].Name, Buf);
      is_ok = false;
      break;
    }
  }
  if (is_ok)
  {
    if ((prg = glCreateProgram()) == 0)
    {
      is_ok = false;
      sprintf(TypeName, "PROG");
      sprintf(ErrText, "Error create program");
      Log(TypeName, ErrText);
    }
    else
    {
      //Attach shaders to program
      for (i = 0; i < Ns; i++)
        if (shd[i].Id != 0)
          glAttachShader(prg, shd[i].Id);
      //Link shader program
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &resources);
      if (resources != 1)
      {
        sprintf(ErrText, "Error create shader");
        glGetProgramInfoLog(prg, sizeof(Buf), &resources, Buf);
        Log(TypeName, Buf);
        is_ok = false;
      }
    }
  }
  //Error handle
  if (!is_ok)
  {
    //Remove all shaders
    for (i = 0; i < Ns; i++)
      if (shd[i].Id != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shd[i].Id);
        glDeleteShader(shd[i].Id);
      }
    //Remove program
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }
  return prg;
}

void shader::Delete( void )
{
  int n, i;
  UINT shdrs[5];
  
  if (ProgId == 0 || !glIsProgram(ProgId))
    return;
  glGetAttachedShaders(ProgId, 5, &n, shdrs);
  for (i = 0; i < n; i++)
  {
    glDetachShader(ProgId, shdrs[i]);
    glDeleteShader(shdrs[i]);
  }
  glDeleteProgram(ProgId);
}

