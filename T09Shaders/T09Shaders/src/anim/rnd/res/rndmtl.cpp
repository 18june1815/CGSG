  #include "rndres.h"
#include "../rnd.h"


material material::DefMaterial( void )
{
  material def_mtl;                       
  strcpy(def_mtl.Name, "Default");
  def_mtl.Ka = dlgl::vec3(0.1, 0.1, 0.1);
  def_mtl.Kd = dlgl::vec3(0.9, 0.9, 0.9);
  def_mtl.Ks = dlgl::vec3(0.3, 0.3, 0.3);
  def_mtl.Ph = 30;
  def_mtl.Trans = 0;
  def_mtl.ShdNo = 0;
  for (int i = 0; i < 8; i++)
    def_mtl.Tex[i] = -1; 
    

  return def_mtl;
}

int resources::ApplyMaterial( int MtlNo )
{
  material *m;
  int loc, prg;

  // Set material pointer
  if (MtlNo < 0 || MtlNo > NumOfMaterials)
    MtlNo = 0;
  m = &mtl[MtlNo];


  // Set program Id
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= NumOfShaders)
    prg = 0;
  prg = shd[prg]->ProgId;
    glUseProgram(prg);

  if((loc = glGetUniformLocation(prg, "Time")) != -1)
    glUniform1f(loc, rnd.T.Time);

  // Set shading parameters
  if((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &m->Ka.X);
  if((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &m->Kd.X);
  if((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &m->Ks.X);
  if((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, m->Ph);
  if((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, m->Trans);

  //Set textures
  for (int i = 0; i < 8; i++)
  {
    char tname[] = "IsTexture0";  

    if (m->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, tex[m->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
  }

  
  return prg;
}

