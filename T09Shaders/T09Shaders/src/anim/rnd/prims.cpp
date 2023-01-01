#include <fstream>

#include "prims.h"
#include "res/rndres.h"

void prims::Delete( void )
{
  for (int i = 0; i < NofElements; i++)
  {
    primitives[i]->Delete();  
    delete[] primitives[i];
  }
}

bool prims::FindStartLines( std::vector<int> &lineNo, const char *FileName )
{
  std::string tmp;
  static char Buf[1000];
  int N = 0;

  FILE *F;
  if ((F = fopen(FileName, "r")) == nullptr)
    return false;

  char oldc = ' ';
   
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ' && oldc != 'v')
      lineNo.push_back(N);
    N++;
    oldc = Buf[0];
  }
  lineNo.push_back(N - 1);

  fclose(F);
  return true;
}

bool prims::Load( const char *FileName )
{
  std::vector<int> lineNo;
  FindStartLines(lineNo, FileName);
  int sum = 0;
  
  for (int i = 0; i < size(lineNo) - 1; i++)
  {
    //primitives.push_back(pr);
    primitives[i] = new prim();
    primitives[i]->Load(FileName, lineNo[i], lineNo[i + 1], sum);
    sum += primitives[i]->NumOfV;
    NofElements++;

    if (MinBB.X > primitives[i]->MinBB.X)
      MinBB.X = primitives[i]->MinBB.X;
    if (MaxBB.X < primitives[i]->MaxBB.X)
      MaxBB.X = primitives[i]->MaxBB.X;

    if (MinBB.Y > primitives[i]->MinBB.Y)
      MinBB.Y = primitives[i]->MinBB.Y;
    if (MaxBB.Y < primitives[i]->MaxBB.Y)
      MaxBB.Y = primitives[i]->MaxBB.Y;

    if (MinBB.Z > primitives[i]->MinBB.Z)
      MinBB.Z = primitives[i]->MinBB.Z;
    if (MaxBB.Z < primitives[i]->MaxBB.Z)
      MaxBB.Z = primitives[i]->MaxBB.Z;
  }
  return true;
}
void prims::SetWorldTransormation( const dlgl::matr &MW )
{
  for (int i = 0; i < NofElements; i++)
    primitives[i]->SetWorldTransormation(MW);
  MatrWorld = MatrWorld * MW;
}

bool prims::LoadG3DM( const char *FileName )
{
  int flen;
  BYTE *ptr;
  std::vector<BYTE> mem;

  std::fstream F(FileName, std::ios::in | std::ios::binary);

  if (!F)
    return false;

  F.seekg(0, std::ios::end);
  flen = (int)F.tellg();
  F.seekg(0, std::ios::beg);

  mem.resize(flen);
  F.read((char *)mem.data(), flen);
  F.close();
 
  DWORD Sign, NumOfPrims, NumOfMaterials, NumOfTextures;
  ptr = mem.data();
  Sign = *(DWORD *)ptr;
  ptr += 4;
  if (Sign != *(DWORD *)"G3DM")
    return false;
  NumOfPrims = *(DWORD *)ptr;
  NofElements = NumOfPrims;
  ptr += 4;
  NumOfMaterials = *(DWORD * )ptr;
  ptr += 4;
  NumOfTextures = *(DWORD * )ptr;
  ptr += 4;
  

  DWORD MtlNo, NumOfV, NumOfI;
  

  for (int p = 0; p < NumOfPrims; p++)
  {
    NumOfV = *(DWORD *)ptr;
    ptr += 4;
    NumOfI = *(DWORD *)ptr;
    ptr += 4;
    MtlNo = *(DWORD *)ptr + rnd->resources.NumOfMaterials;
    ptr += 4;

    std::vector<vertex> V;
    for (int i = 0; i < NumOfV; i++)
    {   
      float x, y, z, tx, ty, nx, ny, nz, cr, cg, cb, ca;
      x = *(float *)ptr;
      ptr += 4;
      y = *(float *)ptr;
      ptr += 4;
      z = *(float *)ptr;
      ptr += 4;
      tx = *(float *)ptr;
      ptr += 4;
      ty = *(float *)ptr;
      ptr += 4;
      nx = *(float *)ptr;
      ptr += 4;
      ny = *(float *)ptr;
      ptr += 4;
      nz = *(float *)ptr;
      ptr += 4;
      cr = *(float *)ptr;
      ptr += 4;
      cg = *(float *)ptr;
      ptr += 4;
      cb = *(float *)ptr;
      ptr += 4;
      ca = *(float *)ptr;
      ptr += 4;
      V.push_back({dlgl::vec3(x, y, z), {tx, ty}, {nx, ny, nz}, {cr, cg, cb, ca}});
    }
     std::vector<int> Ind;
    for (int i = 0; i < NumOfI; i++)
    {   
      Ind.push_back(*(int *)ptr);
      ptr += 4;
    }

    primitives[p] = new prim();
    primitives[p]->Create(V.data(), V.size(), Ind.data(), Ind.size());
    primitives[p]->MtlNo = MtlNo;
    EvalBB(V.data(), V.size());
    
  }

  struct Mtl 
  {
    char Name[300];
    dlgl::vec3 Ka, Kd, Ks;
    float Ph;
    float Trans;
    int Tex[8];

    char ShaderString[300];
    DWORD Shader;
  } *fmat;
         
  for (int m = 0; m < NumOfMaterials; m++)
  {
    material mtl;
  
    fmat = (Mtl *)ptr;
    ptr += sizeof(*fmat);
    mtl.Name = fmat->Name;
    mtl.Ka = fmat->Ka;
    mtl.Kd = fmat->Kd;
    mtl.Ks = fmat->Ks;
    mtl.Ph = fmat->Ph;
    mtl.Trans = fmat->Trans;
    
    for (int t = 0; t < 8; t++)
    {
      if (fmat->Tex[t] != -1)
        mtl.Tex[t] = fmat->Tex[t] + rnd->resources.NumOfTextures;
    }
    MtlNo = rnd->resources.AddMaterial(&mtl) - 1;
  }

  for (int t = 0; t < NumOfTextures; t++)
  {
    char *Name;
    DWORD W, H, C;

    Name = (char *)ptr;
    ptr += 300;
    W = *(DWORD *)ptr;
    ptr += 4;
    H = *(DWORD *)ptr;
    ptr += 4;
    C = *(DWORD *)ptr;
    ptr += 4;

    int TexNo = rnd->resources.AddImg(Name, W, H, C, ptr);
    
    ptr += W * H * C;
  } 
  
  return true;
}



void prims::Draw( dlgl::matr MatrVP )
{
  glEnable(GL_CULL_FACE);

  //Draw all transparent primitives
  for (int i = 0; i < NofElements; i++)
  {
    int MtlNo = primitives[i]->MtlNo;
 
    material *mtl = &(rnd->resources.mtl[MtlNo]);
    
    if (mtl->Trans != 1)
      primitives[i]->Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd, cam);
  }

  // Draw all front-face-culling 
  glCullFace(GL_FRONT);
  for (int i = 0; i < NofElements; i++)
  {
    int MtlNo = primitives[i]->MtlNo;
    material *mtl = &(rnd->resources.mtl[MtlNo]);
    
    if (mtl->Trans == 1)
      primitives[i]->Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd, cam);
  }

  // Draw all back-face-culling 
  glCullFace(GL_BACK);
  for (int i = 0; i < NofElements; i++)
  {
    int MtlNo = primitives[i]->MtlNo;
    material *mtl = &(rnd->resources.mtl[MtlNo]);
    
    if (mtl->Trans == 1)
      primitives[i]->Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd, cam);
  }
  
  glDisable(GL_CULL_FACE);
}


void prims::EvalBB( vertex *V, int NoofV )
{
int i;

  if (V == 0 && NoofV == 0)
    return;

  for (i = 0; i < NoofV; i++)
  {
    if (MinBB.X > V[i].P.X)
      MinBB.X = V[i].P.X;
    if (MaxBB.X < V[i].P.X)
      MaxBB.X = V[i].P.X;

    if (MinBB.Y > V[i].P.Y)
      MinBB.Y = V[i].P.Y;
    if (MaxBB.Y < V[i].P.Y)
      MaxBB.Y = V[i].P.Y;

    if (MinBB.Z > V[i].P.Z)
      MinBB.Z = V[i].P.Z;
    if (MaxBB.Z < V[i].P.Z)
      MaxBB.Z = V[i].P.Z;
  }
  
}

void prims::SetBB( void )
{
  dlgl::vec3 B = MaxBB - MinBB;
  SetWorldTransormation( dlgl::matr::Translate(-MaxBB));
  double sc = B.X;

  if (sc < B.Y)
    sc = B.Y;
  if (sc < B.Z)
    sc = B.Z;

  SetWorldTransormation(dlgl::matr::Scale(dlgl::vec3(1 / sc, 1 / sc, 1 / sc)));
  
}
 
