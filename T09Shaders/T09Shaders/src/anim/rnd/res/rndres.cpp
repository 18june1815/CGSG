#include "anim/rnd/rnd.h"
#include "rndres.h"

void resources::Init( void )
{

  // Init shaders
  NumOfShaders = AddShader("default");
  UpdateShader();

  // Init materials
  material m;
  m = m.DefMaterial(); 
  NumOfMaterials = AddMaterial(&m);

//  LoadFont("bin/fonts/Book.g3df");
}

void resources::Close( void )
{
  
  for (int i = 0; i < NumOfShaders; i++)
    shd[i].Delete();

  //Fnt.Delete();
}

int resources::AddShader( const char *ShaderFileNamePrefix)
{
  for (int i = 0; i < NumOfShaders; i++)
    if (strcmp(shd[i].Name, ShaderFileNamePrefix) == 0)
      return i;
  if (NumOfShaders > MAX_SHADERS)
    return 0;
  
  shd[NumOfShaders++] = shader(ShaderFileNamePrefix);
  
  return NumOfShaders;
}


void resources::UpdateShader( void )
{
  for (int i = 0; i < NumOfShaders; i++)
  {
    shd[i].Delete();
    shd[i].ProgId = shd[i].Load();
  }
}


int resources::AddMaterial( material *Mtl )
{
  mtl[NumOfMaterials++] = *Mtl;

  return NumOfMaterials;  
}


