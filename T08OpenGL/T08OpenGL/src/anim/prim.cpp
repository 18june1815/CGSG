#include <string>
#include <fstream>
#include <cctype>

#include "prim.h"

bool rnd::prim::Create( int NoofV, int NoofI )
{
  if (V != nullptr)
    delete[] V;
  if (I != nullptr)
    delete[] I;
  V = new vertex[NumOfV = NoofV];
  I = new int[NumOfI = NoofI];
  MatrWorld = dlgl::matr::Identity();          
  return true;
} // end of 'Create' function

void rnd::prim::Render( void ) 
{
  dlgl::matr wvp = MatrWorld * MatrVP;
   
  // Draw triangles
  for (int i = 0; i < NumOfI; i += 3)
  {
   /* */
  } 

} // end of Render function

 void rnd::prim::SetWorldTransormation( dlgl::matr MW )
 {
   MatrWorld = MatrWorld * MW;
 }

 bool rnd::prim::Load( const char *FileName )
 {
   FILE *F;
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


   if (!Create(nv, ni * 3))
   {
     fclose(F);
     return false;
   }
   else 
     Create(nv, ni * 3);
 
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
             I[ni++] = n0 - 1;
             I[ni++] = n1 - 1;
             I[ni++] = nc - 1;
             n1 = nc;
           }
           n++;
         }
         oldc = *S++;
       }
     }
   }
  fclose(F);
  return true;
 }
 void rnd::prim::EvalBB( void )
 {
   int i;

   if (V == 0 && NumOfV == 0)
     return;
   MinBB = MaxBB = V[0].P;

   for (i = 0; i < NumOfV; i++)
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

void rnd::prim::SetBB( void )
{
  EvalBB();
  if(NumOfV > 0)
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
}

void rnd::prim::Response( void )
{
}

