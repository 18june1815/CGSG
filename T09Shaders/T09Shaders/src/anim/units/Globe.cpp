#include "Units.h"
#include "anim/anim.h"
 
globe::globe( render *R )
{
  rnd = R;
  int NumOfV, NumOfI;
  
  NumOfV = GLOBE_H * GLOBE_W;
  NumOfI = (GLOBE_H - 1) * (GLOBE_W - 1) * 6;

  Prim.MtlNo = 0;

  GeomSet(0.2);
  GlobeSet();
    
  float Rx = (float) rand()/RAND_MAX - 0.5;
  float Ry = (float) rand()/RAND_MAX - 0.5;
  pos = dlgl::vec3(3 * Rx, 0, 3 * Ry);
    
  Prim.MatrWorld =  Prim.MatrWorld * dlgl::matr::Translate(pos); 
  SetMaterial();
}
  
void globe::GeomSet( double R )
{
  int i, j;
  double theta = 0, phi = 0, tmp;
  for (i = 0, theta = 0; i < GLOBE_H; i++, theta += mth::PI / (GLOBE_H - 1))
    for (j = 0, phi = 0; j < GLOBE_W; j++, phi += 2 * mth::PI / (GLOBE_W - 1))
    {
      tmp = R * sin(theta) * sin(phi);
      Geom[i][j] = dlgl::vec3(R * sin(theta) * sin(phi),
                              R * cos(theta),
                              R * sin(theta) * cos(phi));
    }
} // End of 'GeomSet' function

void globe::GlobeSet( void )
{
  std::vector<vertex> V;
  std::vector<int> Ind;

  float Tx, Ty;
  for (int i = 0; i < GLOBE_H; i++)
  {
    for (int j = 0; j < GLOBE_W; j++)
    {
      Tx = j / (GLOBE_W - 1.0);
      Ty = i / (GLOBE_H - 1.0);
      V.push_back({Geom[i][j], {Tx, Ty}, Geom[i][j].Normalize(), {1, 1, 1, 1}});
      
      if (i != GLOBE_H - 1 && j != GLOBE_W - 1)
      {
        Ind.push_back(i * GLOBE_H + j);
        Ind.push_back(i * GLOBE_H + j + 1);
        Ind.push_back((i + 1) * GLOBE_H + j + 1);
        Ind.push_back(i * GLOBE_H + j);
        Ind.push_back((i + 1) * GLOBE_H + j + 1);
        Ind.push_back((i + 1) * GLOBE_H + j);
         
      }
    } //end for j
  } //end for i

  Prim.Create(V.data(), V.size(), Ind.data(), Ind.size());
} //End of "GlobeSet" function


void globe::Response( void ) 
{
  Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3(0,0.05 * sin(rnd->T.Time * 3 - 30 * pos.X + pos.Y), 0)));
}

void globe::SetMaterial( void )
{
 /* int TexNo = SetTexture();
  material m = material::DefMaterial();
  float
    R1 = (float) rand()/RAND_MAX,
    R2 = (float) rand()/RAND_MAX,
    R3 = (float) rand()/RAND_MAX;
  dlgl::vec3 color = dlgl::vec3(R1, R2, R3);
  m.Tex[0] = TexNo; 
  m.Name = "Globe";
  */
  if (rnd->resources.FindMaterial("Silver") == -1)
  {
    material m = material::GetLibMaterial("Silver");
    Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
  }
  else 
    Prim.MtlNo = rnd->resources.FindMaterial("Silver");
}

int globe::SetTexture( void )
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
      TexNo = rnd->resources.AddImg("Globe", w, h, 3, mem);

      delete[] mem;
    }
    fclose(F);
  }
  return TexNo;
}

void globe::Draw( dlgl::matr MatrVP  )
{
    Prim.Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd);
}
