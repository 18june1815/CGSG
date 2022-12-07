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
 
  FILE *F;
  int flen;
  BYTE *mem, *ptr;
  

  if ((F = fopen(FileName, "rb")) == NULL)
    return false;

  fseek(F, 0, SEEK_END);
  flen = ftell(F);
  rewind(F);

  mem = (BYTE *)malloc(flen);
  fread(mem, sizeof(BYTE), flen, F);
  fclose(F);
 
  DWORD Sign, NumOfPrims, NumOfMaterials, NumOfTextures;
  ptr = mem;
  Sign = *(DWORD *)ptr;
  ptr += 4;
  if (Sign != *(DWORD *)"G3DM")
  {
    delete mem;
    return false;
  }
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
        float a = 5;
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

   // BYTE *TextureImage = (BYTE *)malloc(W * H * C);
    
    //if (rnd->resources.FindTexture(Name) == -1)

    int TexNo = rnd->resources.AddImg(Name, W, H, C, ptr);
    //rnd->resources.AddTexture(&mtl, mtl.Name, "bin/textures/sky_sphere.bmp");
    
    ptr += W * H * C;
   } 
  

  free(mem);

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
      primitives[i]->Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd);
  }

  // Draw all front-face-culling 
  glCullFace(GL_FRONT);
  for (int i = 0; i < NofElements; i++)
  {
    int MtlNo = primitives[i]->MtlNo;
    material *mtl = &(rnd->resources.mtl[MtlNo]);
    
    if (mtl->Trans == 1)
      primitives[i]->Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd);
  }

  // Draw all back-face-culling 
  glCullFace(GL_BACK);
  for (int i = 0; i < NofElements; i++)
  {
    int MtlNo = primitives[i]->MtlNo;
    material *mtl = &(rnd->resources.mtl[MtlNo]);
    
    if (mtl->Trans == 1)
      primitives[i]->Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd);
  }
  
  glDisable(GL_CULL_FACE);
}
