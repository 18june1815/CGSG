#include "Units.h"
/*noise_shd::noise_shd( render *R, camera *c )
{
  name = "Noise";
  rnd = R;
  cam = c;
  
  NoiseInit();

  for (int y = 0; y < GRID_SIZE; y++)
    for (int x = 0; x < GRID_SIZE; x++)
    {
      g->V[y * g->W + x].P = 
          dlgl::vec3(size * x / (GRID_SIZE - 1.0) - size /2.,
                      NoiseTurb2D(x * 0.2, y * 0.3, Oct) * 5,
                      //NoiseTurb1D(x, Oct),
                      size * (1 - y / (GRID_SIZE - 1.0)) - size / 2.);
      //V[y * g->W + x].P = g->V[y * g->W + x].P;
    }
    
  g->AutoNormals();
  g->PrimFromGrid(Prim);
  
  SetMaterial();
  Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3(0, -5, 0)));
 
}

void noise_shd::Delete( void )
{
  delete g;
}

void noise_shd::Draw( dlgl::matr MatrVP )
{
   Prim.Draw(PolygonMode, GL_TRIANGLE_STRIP, MatrVP, rnd, cam);
  //Prim.Draw(GL_LINE, GL_TRIANGLE_STRIP, MatrVP, rnd, cam);
}


void noise_shd::SetMaterial( void )
{
  material m = material::DefMaterial();
  Prim.MtlNo = rnd->resources->AddMaterial(&m) - 1;
}

void noise_shd::Response( void ) 
{
  for (int y = 0; y < GRID_SIZE; y++)
    for (int x = 0; x < GRID_SIZE; x++)
    {
      g->V[y * g->W + x].P.Y = NoiseTurb2D(x * 0.2, y * 0.3 + rnd->T.Time, Oct) * 5;
    }
  g->AutoNormals();  
  for (int y = 0; y < GRID_SIZE; y++)
    for (int x = 0; x < GRID_SIZE; x++)
    {
      V[y * g->W + x].P = g->V[y * g->W + x].P;
      V[y * g->W + x].N = g->V[y * g->W + x].N;
    }
  glBindBuffer(GL_ARRAY_BUFFER, Prim.VBuf);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex) * GRID_SIZE * GRID_SIZE, V);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
}


void noise_shd::Keyboard( BYTE Keys[256], int IsDown )
{
  /*
   if (! rnd->T.IsPause)
  {
    if (Keys[VK_UP])
      Oct++, Oct &= 7;
    if (Keys[VK_DOWN])
      Oct--, Oct &= 7;
   }
   
}
   */


