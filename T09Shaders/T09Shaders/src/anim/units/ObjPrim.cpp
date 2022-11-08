#include "Units.h"

objprim::objprim( const char *FN, render *R )
{
  rnd = R;
  Prim.MtlNo = 0;
  Load(FN);
  SetMaterial();
}
  
bool objprim::Load( const char *FileName )
{
  FILE *F;
  std::vector<vertex> V;
  std::vector<int> Ind;
  int nv = 0, ni = 0;
  static char Buf[1000];

  Prim.Trans = dlgl::matr::Identity();
  if ((F = fopen(FileName, "r")) == nullptr)
    return false;

  // Read model data
  rewind(F);
  nv = 0;
  ni = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      double x, y ,z;
      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V.push_back({dlgl::vec3(x, y, z), {0, 0}, {0, 0, 0}, {1, 1, 1, 1}});
      

    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      char *S = Buf + 2, oldc = ' ';
      int n = 0, n0 = 0, n1 =0, nc;
       
      while (*S != 0)
      {
        if (isspace((UCHAR)oldc) && !isspace((UCHAR)*S))
        {
          sscanf(S, "%d", &nc);

          if (n == 0)
            n0 = nc;
          else if (n == 1)
            n1 = nc;
          else
          {
            Ind.push_back(n0 - 1);
            Ind.push_back(n1 - 1);
            Ind.push_back(nc - 1);
            n1 = nc;
          }
          n++;
        }
        oldc = *S++;
      }
    }
  }
  fclose(F);

  Prim.Autonormals(V.data(), V.size(), Ind.data(), Ind.size());
  Prim.Create(V.data(), V.size(), Ind.data(), Ind.size());
  Prim.SetBB(V.data(), V.size());

  Prim.SetWorldTransormation(dlgl::matr::Scale({3, 3, 3}));

  return true;
}
void objprim::SetMaterial( void )
{
  //int TexNo = SetTexture();
  material m = material::DefMaterial();
  m.Name = "ObjPrim";
  m.Ka = dlgl::vec3(0.9, 0.1, 0.5);
  m.Ks = dlgl::vec3(0.9, 0.1, 0.5);
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
}


int objprim::SetTexture( void )
{
  FILE *F;
    
  
  static int TexNo = -1;
  if (TexNo == -1)
  {
    if ((F = fopen("bin/textures/GLOBE.G24", "rb")) != NULL)
    {
      int w = 0, h = 0;
        
      fread(&w, 2, 1, F);
      fread(&h, 2, 1, F);

      BYTE  *mem = new BYTE[w * h * 3];
      // int n;
      fread(mem, 3, w * h, F);
      TexNo = rnd->resources.AddImg("Cow", w, h, 3, mem);

      delete[] mem;
    }
    fclose(F);
  }
  return TexNo;
}


void objprim::Draw( dlgl::matr MatrVP  ) 
{
  Prim.Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd);
}
