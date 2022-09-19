#ifndef __OBJPRIM_H_
#define __OBJPRIM_H_

#include "anim/prim.h"

class objprim : public prim
{
public:
  objprim ( const char *FN )
  {
    MtlNo = 0;
    Load(FN);
    SetMaterial();
  }
  
  bool Load( const char *FileName )
  {
    FILE *F;
    vertex *V;
    int *Ind;
    int nv = 0, ni = 0;
    static char Buf[1000];

    if ((F = fopen(FileName, "r")) == nullptr)
      return false;

    while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    {
      if (Buf[0] == 'v' && Buf[1] == ' ')
        nv++;
      else if (Buf[0] == 'f' && Buf[1] == ' ')
      {
        char *S = Buf + 2, oldc = ' ';
        int cnt = 0;

        while (*S != 0)
          cnt += isspace((UCHAR)oldc) && !isspace((UCHAR)*S), oldc = *S++;
        ni += cnt - 2;
      }
    }

    V = new vertex[nv];
    Ind = new int[ni * 3];

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
        V[nv++].P = dlgl::vec3(x, y ,z);

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
              Ind[ni++] = n0 - 1;
              Ind[ni++] = n1 - 1;
              Ind[ni++] = nc - 1;
              n1 = nc;
            }
            n++;
          }
          oldc = *S++;
        }
      }
    }
    fclose(F);

    Autonormals(V, nv, Ind, ni);
    Create(V, nv, Ind, ni);
    SetBB(V, nv);

    SetWorldTransormation(dlgl::matr::Scale(dlgl::vec3(3, 3, 3)));

    delete[] V;
    delete[] Ind;
    return true;      
  }
  void SetMaterial( void )
  {
    material m = material::DefMaterial();
    m.Ka = dlgl::vec3(1, 0, 0);
    m.Kd = dlgl::vec3(0.5, 0.5, 0.8);
    m.Ks = dlgl::vec3(0., 0., 1);
    m.Ph = 50;
    MtlNo = rnd.resources.AddMaterial(&m) - 1;
  }

};

#endif /* __OBJPRIM_H_ */
