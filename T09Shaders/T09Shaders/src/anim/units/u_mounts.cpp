#include "Units.h"
#include "../rnd/grid.h"  

u_mounts::u_mounts()
{
  float size = 300, h = 30;
  HBITMAP hBm;

  hBm = (HBITMAP)LoadImage(NULL, "bin/textures/hf.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
  if (hBm != NULL)
  {
    BITMAP bm;
    GetObject(hBm, sizeof(bm), &bm);
    grid g(bm.bmWidth, bm.bmHeight);

    for (int y = 0; y < bm.bmHeight; y++)
      for (int x = 0; x < bm.bmWidth; x++)
      {

        BYTE c = *((BYTE *)bm.bmBits + bm.bmWidthBytes * y + x);
        g.V[y * g.W + x].P = 
            dlgl::vec3(size * x / (bm.bmWidth - 1.0) - size /2.,
                       h * c / 255.0,
                       size * (1 - y / (bm.bmHeight - 1.0)) - size / 2.);
      }

    g.AutoNormals();
    g.PrimFromGrid(Prim);
    DeleteObject(hBm);
  }
  SetMaterial();
  Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3(0, -5, 0)));
       
}


void u_mounts::Draw( dlgl::matr MatrVP )
{
  Prim.Draw(GL_FILL, GL_TRIANGLE_STRIP, MatrVP);
}


void u_mounts::SetMaterial( void )
{
  material m = material::DefMaterial();
  int TexNo = SetTexture();
  dlgl::vec3 color = dlgl::vec3(0.5, 0.5, 0);
  m.Ka = color * 0.1;
  m.Kd = color * 0.8;
  m.Ks = color * 0.9;
  m.Ph = 50;
  m.Tex[0] = TexNo; 
  Prim.MtlNo = rnd.resources.AddMaterial(&m) - 1;
}

int u_mounts::SetTexture( void )
{
  HBITMAP hBm;
    
  static int TexNo = -1;
  if (TexNo == -1)
  {
    hBm = (HBITMAP)LoadImage(NULL, "bin/textures/hftex.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (hBm != NULL)
    {
      BITMAP bm;
      GetObject(hBm, sizeof(bm), &bm);

      BYTE *mem = (BYTE *)bm.bmBits;
      TexNo = rnd.resources.AddImg("Mounts", bm.bmWidth, bm.bmHeight, 3, mem);
      DeleteObject(hBm);
    }
  }
  return TexNo;
}


void u_mounts::Response( void ) 
{
  //Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3(0, 0.05, 0)));
}
