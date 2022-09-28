#include <string>
#include <fstream>
#include <cctype>
#include <vector>

#include "prim.h"
#include "rnd/rnd.h"

void prim::Create( vertex *V, int NoofV, int *Ind, int NoofI )
{
  dlgl::vec3 L(0.5, 1, 1);
  L = L.Normalize();

  for (int i = 0; i < NoofV; i++)
  {
    float nl = (V[i].N & L);

    V[i].C = dlgl::vec4(nl * 0.1 + V[i].N.X, nl * 0.3 + V[i].N.Y, nl * 0.60 + V[i].N.Z, 0);
    V[i].C = dlgl::vec4(nl * 0.3 + 0.5, nl * 0.3 +0.2, nl * 0.60 + 0.3, 0);
    //V[i].C = dlgl::vec4(V[i].N.X, V[i].N.Y, V[i].N.Z, 0);
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
  int loc, ProgId;
  
  dlgl::matr 
    wvp = MatrWorld * MatrVP,
    w = MatrWorld,
    winv = w.Inverse();

  glLoadMatrixf(wvp.M[0]);
     
  // Pass render uniforms
  ProgId = rnd.resources.ApplyMaterial(MtlNo);  
   if ((loc = glGetUniformLocation(rnd.resources.shd[0].ProgId, "Time")) != -1)
    glUniform1f(loc, rnd.T.Time);
  if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.M[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrW")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, w.M[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrWInv")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, winv.M[0]);
  if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1)
    glUniformMatrix3fv(loc, 1, FALSE, &rnd.cam.Loc.X); 
  
    
  // Draw triangles
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
  glUseProgram(rnd.resources.shd[0].ProgId);

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
  std::vector<vertex> VV
  {
    {dlgl::vec3(-1,-1,0)},
    {dlgl::vec3( 1,-1,0)},
    {dlgl::vec3( -1,-1,1)},
    {dlgl::vec3(1,-1,1)},
    {dlgl::vec3( 0,1,0.5)},
  };
  std::vector<int> I {0,1,4,1,3,4,3,2,4,0,2,4,0,2,3,0,1,3};
  Create(VV.data(), VV.size(), I.data(), I.size());
  return true;
 } 
 

void prim::SetMaterial( void )
{
  MtlNo = 0;
}
