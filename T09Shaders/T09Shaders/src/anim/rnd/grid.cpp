#include "grid.h"

grid::grid( int w, int h ) : W(w), H(h)
{
  for (int i = 0; i < H; i++)
    for(int j = 0; j < W; j++)
    {
      V.push_back({dlgl::vec3(float(-j/5.), -1, float(-i/5.)), 
                      {float(j / (W - 1.0)),  float(i / (H - 1.0))},
                      {0, 1, 0}, {1, 0, 0, 1}});
    }
}


void grid::AutoNormals( void ) 
{
  for (int i = 0; i < H - 1; i++)
    for (int j = 0; j < W - 1; j++)
    {
      vertex 
        *P00 = &V[i * W + j],
        *P01 = &V[i * W + j + 1],
        *P10 = &V[(i + 1) * W + j],
        *P11 = &V[(i + 1) * W + j + 1];
      dlgl::vec3 N;

      N = ((P00->P - P10->P).Cross(P11->P - P10->P)).Normalize();
      P00->N = P00->N + N;
      P10->N = P10->N + N;
      P11->N = P11->N + N;
      N = ((P11->P - P01->P).Cross(P00->P - P01->P)).Normalize();
      P00->N = P00->N + N;
      P01->N = P10->N + N;
      P11->N = P11->N + N;
    }
  for (int i = 0; i < W * H; i++)
    V[i].N = V[i].N.Normalize();
 
}

void grid::PrimFromGrid( prim &Prim )
{
     
  std::vector<int> Ind;

  for (int i = 0; i < H - 1; i++)
  {
    for (int j = 0; j < W; j++)
    {
      Ind.push_back((i + 1) * W + j);
      Ind.push_back(i * W + j);
    }
    if (i != H - 2)
      Ind.push_back(-1);
  }
  Prim.Create(V.data(), V.size(), Ind.data(), Ind.size());
       
}

bool grid::CreateSphere( float R )
{
  int i, j, k;
  double theta = 0, phi = 0;

  for (i = 0, theta = 0, k = 0; i < H; i++, theta += mth::PI / (H - 1))
    for (j = 0, phi = 0; j < W; j++, phi += 2 * mth::PI / (W - 1))
    {
      V[k].P = dlgl::vec3(R * sin(theta) * sin(phi),
                          R * cos(theta),
                          R * cos(phi) * sin(theta)); 
      V[k].N = dlgl::vec3(sin(theta) * sin(phi),
                          cos(theta),
                          cos(phi) * sin(theta));
      V[k].T.X = j / (W - 1.0); 
      V[k].T.Y = i / (H - 1.0); 

      k++;
    }
  
  return true;
}

void grid::CreateMounts( void )
{
  float size = 3, h = 10;
  HBITMAP hBm;

  hBm = (HBITMAP)LoadImage(NULL, "bin/textures/hf.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
  if (hBm != NULL)
  {
    BITMAP bm;
    GetObject(hBm, sizeof(bm), &bm);
   
    W = bm.bmWidth;
    H = bm.bmHeight;

    for (int y = 0; y < bm.bmHeight; y++)
      for (int x = 0; x < bm.bmWidth; x++)
      {
        V.push_back({dlgl::vec3(float(-x/5.), -1, float(-y/5.)), 
                      {float(x / (W - 1.0)),  float(y / (H - 1.0))},
                      {0, 1, 0}, {1, 0, 0, 1}});

        BYTE c = *((BYTE *)bm.bmBits + bm.bmWidthBytes * y + x);
        V[y * W + x].P = 
          dlgl::vec3(float(-x/5.),//x / (bm.bmWidth) - size /2,
                     h * c / 255.0,
                     float(-y/5.));//size * (1 - y / (bm.bmHeight - 1.0)) - size / 2);
      }
   // PrimFromGrid(Prim);
    DeleteObject(hBm);
  }
}
