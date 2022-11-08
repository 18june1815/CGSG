#include "Units.h"
#include "../rnd/grid.h"  

u_grid::u_grid( render *Rnd )
{
  rnd = Rnd;
  int W = 50, H = 50, R = 100.;
  grid g(W, H);

  g.CreateSphere(R);

  g.PrimFromGrid(Prim);
  SetMaterial();
  Prim.SetWorldTransormation(dlgl::matr::Rotate(dlgl::vec3(1, 0, 0), 180));
}

void u_grid::Draw( dlgl::matr MatrVP )
{
  Prim.Draw(GL_FILL, GL_TRIANGLE_STRIP, MatrVP, rnd);
}


void u_grid::SetMaterial( void )
{ 
  material m = material::DefMaterial();
  int TexNo = SetTexture();
  dlgl::vec3 color = dlgl::vec3(0.5, 0.5, 0);
  m.Tex[0] = TexNo; 
  m.Name = "Sky";
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
}


int u_grid::SetTexture( void )
{
  HBITMAP hBm;
    
  static int TexNo = -1;
  if (TexNo == -1)
  {
    hBm = (HBITMAP)LoadImage(NULL, "bin/textures/sky_sphere.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (hBm != NULL)
    {
      BITMAP bm;
      GetObject(hBm, sizeof(bm), &bm);

      BYTE *mem = (BYTE *)bm.bmBits;
      TexNo = rnd->resources.AddImg("Sky", bm.bmWidth, bm.bmHeight, 3, mem);
      DeleteObject(hBm);
    }
  }
  return TexNo;
}
