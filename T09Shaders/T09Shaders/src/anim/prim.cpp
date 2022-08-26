#include <string>
#include <fstream>
#include <cctype>

#include "prim.h"
#include "rnd/rnd.h"

void prim::Create( vertex *V, int NoofV, int *Ind, int NoofI )
{
  dlgl::vec3 L(0.5, 1, 1);
  L = L.Normalize();

  for (int i = 0; i < NoofV; i++)
  {
    float nl = (V[i].N & L);

    V[i].C = dlgl::vec4(nl * 0.8 + V[i].N.X, nl * 0.3 + V[i].N.Y, nl * 0.60 + V[i].N.Z, 0);
  }
  
     
  glGenBuffers(1, &VBuf);
  glGenVertexArrays(1, &VA);

  glBindVertexArray(VA);
  glBindBuffer(GL_ARRAY_BUFFER, VBuf);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * NoofV, V, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(vertex), (VOID *)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(vertex), (VOID *)sizeof(dlgl::vec3));
  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(vertex), 
                        (VOID *)(sizeof(dlgl::vec3) + sizeof(dlgl::vec2)));
  glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(vertex), 
                        (VOID *)(sizeof(dlgl::vec3) * 2 + sizeof(dlgl::vec2)));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glBindVertexArray(0);

  if (NoofI != 0)
  {
    glGenBuffers(1, &IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * NoofI, Ind, GL_STATIC_DRAW);
    NumOfElements = NoofI;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  else
    NumOfElements = NoofV;

  MatrWorld = dlgl::matr::Identity();          
  
} // end of 'Create' function

void prim::Autonormals( vertex *V, int NoofV, int *Ind, int NoofI )
{
  for (int i = 0; i < NoofV; i++)
    V[i].N = dlgl::vec3(0, 0, 0);
  for (int i = 0; i < NoofI; i += 3)
  {
    dlgl::vec3
      p0 = V[Ind[i]].P,
      p1 = V[Ind[i + 1]].P,
      p2 = V[Ind[i + 2]].P,
      N = ((p0 - p1).Cross(p2 - p0)).Normalize();
    
    V[Ind[i]].N = V[Ind[i]].N + N;
    V[Ind[i + 1]].N = V[Ind[i + 1]].N + N;
    V[Ind[i + 2]].N = V[Ind[i + 2]].N + N;
  }
  for (int i = 0; i < NoofV; i++)
    V[i].N = (V[i].N).Normalize();
}

void prim::Draw( dlgl::matr MatrVP ) 
{
  int loc;

  dlgl::matr wvp = MatrWorld * MatrVP;
   
  glLoadMatrixf(wvp.M[0]);
  // Draw triangles
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
  glUseProgram(rnd.res.shd.ProgId);

  if ((loc = glGetUniformLocation(rnd.res.shd.ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.M[0]);
  if ((loc = glGetUniformLocation(rnd.res.shd.ProgId, "Time")) != -1)
    glUniform1f(loc, rnd.T.Time);

  glBindVertexArray(VA);

  if(IBuf == 0)
    glDrawArrays(GL_TRIANGLES, 0, NumOfElements);
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
    glDrawElements(GL_TRIANGLES, NumOfElements, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  glUseProgram(0);
} // end of Draw function

void prim::SetWorldTransormation( dlgl::matr MW )
{
  MatrWorld = MatrWorld * MW;
}


bool prim::Load( const char *FileName )
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

void prim::EvalBB( vertex *V, int NoofV )
{
int i;

  if (V == 0 && NumOfElements == 0)
    return;
  MinBB = MaxBB = V[0].P;

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

void prim::SetBB( vertex *V, int NoofV )
{
  EvalBB(V, NoofV);
  if(NoofV > 0)
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
 

void prim::Response( void )
{
}

bool prim::LoadTriangle( void )
{
  vertex *V;
  int *Ind;
  int nv = 5, ni = 6;

  V = new vertex[nv];
  Ind = new int[ni * 3];

  V[0].P = dlgl::vec3(-1,-1,0);
  V[1].P = dlgl::vec3( 1,-1,0);
  V[2].P = dlgl::vec3( -1,-1,1);
  V[3].P = dlgl::vec3(1,-1,1);
  V[4].P = dlgl::vec3( 0,1,0.5);

  for(int i = 0; i < nv; i++)
    V[i].C = dlgl::vec4(1, 0, 0, 0);

  GLubyte I[] = {0,1,4,1,3,4,3,2,4,0,2,4,0,2,3,0,1,3};
   
  for(int i = 0; i < ni; i++)
    Ind[i] = I[i];

  Create(V, nv, Ind, ni);
 
  delete[] V;
  delete[] Ind;
  return true;
      
 } 
 

