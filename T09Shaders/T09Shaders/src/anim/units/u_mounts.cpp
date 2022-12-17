#include "Units.h"
#include "../rnd/grid.h"  

u_mounts::u_mounts( render *R, camera *c )
{
  name = "Mounts";
  rnd = R;
  cam = c;
  
  //HBITMAP hBm;
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
    //DeleteObject(hBm);
  }
  SetMaterial();
  Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3(0, -5, 0)));
}

void u_mounts::Delete( void )
{
  DeleteObject(hBm);
}

void u_mounts::Draw( dlgl::matr MatrVP )
{
  Prim.Draw(GL_FILL, GL_TRIANGLE_STRIP, MatrVP, rnd, cam);
}


void u_mounts::SetMaterial( void )
{
  material m = material::GetLibMaterial("Mounts");
  rnd->resources.AddTexture(&m, "Mounts", "bin/textures/hftex.bmp");
  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
}

void u_mounts::Response( void ) 
{
  //Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3(0, 0.05, 0)));
}

void u_mounts::ToPicCoors( dlgl::vec3 P, float &H )
{
  if (hBm != NULL)
  {
    int x, y;
    BITMAP bm;
    GetObject(hBm, sizeof(bm), &bm);

    x = (bm.bmWidth - 1.0) / size * (P.X + size / 2.);
    y = (bm.bmHeight - 1.) / size * (size / 2. - P.Z);
    BYTE c = *((BYTE *)bm.bmBits + bm.bmWidthBytes * y + x);
    H = h * c / 255.0 - 5;
   }
}