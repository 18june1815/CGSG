#include "Units.h"

objprim::objprim( const char *FN )
{
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
  material m = material::DefMaterial();
  m.Ka = dlgl::vec3(1, 0, 0);
  m.Kd = dlgl::vec3(0.5, 0.5, 0.8);
  m.Ks = dlgl::vec3(0., 0., 1);
  m.Ph = 50;
  Prim.MtlNo = rnd.resources.AddMaterial(&m) - 1;
}

void objprim::Draw( dlgl::matr MatrVP  ) 
{
  Prim.Draw(MatrVP);
}
