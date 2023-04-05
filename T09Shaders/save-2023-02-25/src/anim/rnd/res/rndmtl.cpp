#include "rndres.h"
#include "../rnd.h"


static struct
{
  std::string Name;
  dlgl::vec3 Ka, Kd, Ks;
  float Ph;
} MatLib[] =
{
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},               32      },
  {"Brass",         {0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843}, 27.8974  },
  {"Bronze",        {0.2125,0.1275,0.054},       {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},  25.6},
  {"Chrome",        {0.25, 0.25, 0.25},          {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597}, 76.8},
  {"Copper",        {0.19125,0.0735,0.0225},     {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},  12.8},
  {"Gold",          {0.24725,0.1995,0.0745},     {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},  51.2},
  {"Peweter",       {0.10588,0.058824,0.113725}, {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},      9.84615},
  {"Silver",        {0.19225,0.19225,0.19225},   {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},  51.2},
  {"Polished Silver", {0.23125,0.23125,0.23125}, {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},  89.6},
  {"Turquoise",     {0.1, 0.18725, 0.1745},      {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678}, 12.8},
  {"Ruby",          {0.1745, 0.01175, 0.01175},  {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959}, 76.8},
  {"Polished Gold", {0.24725, 0.2245, 0.0645},   {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006}, 83.2},
  {"Polished Bronze", {0.25, 0.148, 0.06475},    {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621}, 76.8},
  {"Polished Copper", {0.2295, 0.08825, 0.0275}, {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 51.2},
  {"Jade",          {0.135, 0.2225, 0.1575},     {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228}, 12.8},
  {"Obsidian",      {0.05375, 0.05, 0.06625},    {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435}, 38.4},
  {"Pearl",         {0.25, 0.20725, 0.20725},    {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648}, 11.264},
  {"Emerald",       {0.0215, 0.1745, 0.0215},    {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},       76.8},
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                32.0},
  {"Black Rubber",  {0.02, 0.02, 0.02},          {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                10.0},
  {"Mounts",        {0.0, 0.9, 0.5},             {0.5, 0.5, 0.5},              {0.05, 0.05, 0.05},             1.0},
};
#define MAT_N (sizeof(MatLib) / sizeof(MatLib[0]))


material material::GetLibMaterial( std::string mtlName )
{
  material mtl;  

  for (int i = 0; i < MAT_N; i++)
  {
    if (mtlName == MatLib[i].Name)
    {
      mtl.Name = mtlName;
      mtl.Ka = MatLib[i].Ka;
      mtl.Kd = MatLib[i].Kd;
      mtl.Ks = MatLib[i].Ks;
      mtl.Ph = MatLib[i].Ph;
      mtl.Trans = 1;
      mtl.ShdNo = 0;
      for (int i = 0; i < 8; i++)
        mtl.Tex[i] = -1; 
    } 
  }
   
  return mtl;
}

material material::DefMaterial( void )
{
  material def_mtl;                       

  def_mtl.Name = "Default";
  def_mtl.Ka = dlgl::vec3(0.5, 0.5, 0.5);
  def_mtl.Kd = dlgl::vec3(0.9, 0.9, 0.9);
  def_mtl.Ks = dlgl::vec3(0.3, 0.3, 0.3);
  def_mtl.Ph = 30;
  def_mtl.Trans = 1;
  def_mtl.ShdNo = 0;
  for (int i = 0; i < 8; i++)
    def_mtl.Tex[i] = -1; 
    
  return def_mtl;
}



int res::ApplyMaterial( int MtlNo, UINT64 Time )
{
  material *m;
  int loc, prg;

  // Set material pointer
  if (MtlNo < 0 || MtlNo > NumOfMaterials)
    MtlNo = 0;
  m = &mtl[MtlNo];


  // Set program Id
  prg = m->ShdNo;
  if (prg < 0 || prg >= NumOfShaders)
    prg = 0;
  prg = shd[prg].ProgId;
    glUseProgram(prg);

  if((loc = glGetUniformLocation(prg, "Time")) != -1)
    glUniform1f(loc, Time);

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

    tname[9] = '0' + i;
    if (m->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, tex[m->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
        glUniform1i(loc, m->Tex[i] != -1);
  }

  return prg;
}


int res::FindMaterial( std::string name )
{
  int mtlNo = -1;
  for (int i = 0; i < NumOfMaterials; i++)
  {
    if (name == mtl[i].Name)
    {
      mtlNo = i;
    }
  }
  return mtlNo;
}