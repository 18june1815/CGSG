#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <map>
#include <tuple>

#include "prim.h"

//#include "rnd/rnd.h"

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

void prim::Draw( int PolygonMode, int ElementsMode, const dlgl::matr &MatrVP, render *rnd ) 
{
  int loc, ProgId;
  
  dlgl::matr 
    wvp = MatrWorld * MatrVP,
    w = MatrWorld,
    winv = w.Inverse();

  glLoadMatrixf(wvp.M[0]);
     
  // Pass render uniforms
  ProgId = rnd->resources.ApplyMaterial(MtlNo, rnd->T.Time);  
   if ((loc = glGetUniformLocation(rnd->resources.shd[0].ProgId, "Time")) != -1)
    glUniform1f(loc, rnd->T.Time);
  if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.M[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrW")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, w.M[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrWInv")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, winv.M[0]);
  if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1)
    glUniform3fv(loc, 1, &rnd->cam.Loc.X); 
  
    
  // Draw triangles
  glPolygonMode(GL_FRONT_AND_BACK, PolygonMode);
  
  glUseProgram(rnd->resources.shd[0].ProgId);

  glBindVertexArray(VA);

  if(IBuf == 0)
    glDrawArrays(GL_TRIANGLES, 0, NumOfElements);
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
    glDrawElements(ElementsMode, NumOfElements, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  glUseProgram(0);
} // end of Draw function

void prim::SetWorldTransormation( const dlgl::matr &MW )
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

bool prim::Load( const char *FileName )
{
  FILE *F;
  std::vector<vertex> V;
  std::vector<int> Ind;
  int nv = 0, ni = 0;
  static char Buf[1000];

  Trans = dlgl::matr::Identity();
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

  Autonormals(V.data(), V.size(), Ind.data(), Ind.size());
  Create(V.data(), V.size(), Ind.data(), Ind.size());
  SetBB(V.data(), V.size());

  return true;
}



bool prim::LoadNew( const char *FileName )
{
  
  std::ifstream F(FileName); 
  std::vector<vertex> V;
  std::vector<dlgl::vec3> v, vn;
  std::vector<dlgl::vec2> vt;
  std::vector<int> Ind;
  std::map<std::string, int> Vmap;
  int ni = 1;
  static std::string Buf;

  Trans = dlgl::matr::Identity();
  
  // Read model data
  
  ni = 0;

   v.push_back(dlgl::vec3(0, 0, 0));
   vt.push_back(dlgl::vec2(0, 0));
   vn.push_back(dlgl::vec3(0, 0, 0));
  while (!F.eof())
  {
    F >> Buf;
    if (Buf == "v")
    {
      double x, y ,z;
      F >> x >> y >> z;
      v.push_back(dlgl::vec3(x, y, z));
    }
    if (Buf == "vt")
    {
      double x, y;
      F >> x >> y;
      vt.push_back(dlgl::vec2(x, y));
    }
    if (Buf == "vn")
    {
      double x, y ,z;
      F >> x >> y >> z;    
      vn.push_back(dlgl::vec3(x, y, z));
    }

    else if (Buf == "f")
    {               
      std::string Sstr, line;
      int nc, nv, nt, nn;
      int n = 0, n0 = 0, n1 =0;
      const char *S;
      char  oldc = ' ';
      std::getline(F, line);
      std::istringstream iss(line);
     // std::tuple<int, int, int> t;
  
      while (iss >> Sstr)
      {
        if (Vmap.find(Sstr) == Vmap.end() )
        {
          S = Sstr.c_str();
         
          nn = nv = nt = 0;
          while (*S != 0)
          {
             if (nv == 0)
               sscanf(S, "%d", &nv);
             else if (nt == 0 && size(vt) > 1 && oldc == 47)
               sscanf(S, "%d", &nt);
             else if (nn == 0 && oldc == 47)
               sscanf(S, "%d", &nn);
             oldc = *S++;
          }
          
          V.push_back({v[nv], vt[nt], vn[nn], {1, 1, 1, 1}});
          Vmap[Sstr] = (nc = ++ni); 

          if ( nv != nn)
            nv = nn;
        }
        else 
        {
          nc = Vmap[Sstr];
        }    
       
         //Ind.push_back(nc);
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
    }
  }

  F.close();

  Create(V.data(), V.size(), Ind.data(), Ind.size());
  SetBB(V.data(), V.size());
  return true;
}