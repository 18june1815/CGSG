#include "Units.h"
 /*
#define INDEX1(X) (Perm[(X) & TAB_MASK])
#define INDEX2(X, Y) (Perm[(X + INDEX1(Y)) & TAB_MASK])
#define INDEX3(X, Y, Z) (Perm[(X + INDEX2(Y, Z)) & TAB_MASK])

void noise::NoiseInit( void )
{
  for (int i = 0; i < TAB_SIZE; i++)
    TabNoise[i] = (double)rand() / RAND_MAX;

  for (int i = 0; i < TAB_SIZE; i++)
    Perm[i] = i;
  for (int i = 0; i < TAB_SIZE * 8; i++)
  {
    int 
      a = rand() & TAB_MASK,
      b = rand() & TAB_MASK,
      tmp = Perm[a];
    Perm[a] = Perm[b];
    Perm[b] = tmp;
  }
}

double noise::Noise1D( double X )
{
  int ix = floor(X), ix1;
  double fx;

  fx = X - ix;
  ix &= TAB_MASK;
  ix1 = (ix + 1) & TAB_MASK;
  return TabNoise[ix] * (1 - fx) + TabNoise[ix1] * fx;
}

double noise::Noise2D( double X, double Y )
{
  int ix = floor(X), ix1, iy = floor(Y), iy1;
  double fx, fy;

  fx = X - ix;
  fx = (3 - 2 * fx) * fx * fx;
  fy = Y - iy;
  fy = (3 - 2 * fy) * fy * fy;
  ix &= TAB_MASK;
  ix1 = (ix + 1) & TAB_MASK;
  iy &= TAB_MASK;
  iy1 = (iy + 1) & TAB_MASK;
  return 
    TabNoise[INDEX2(iy, ix)] * (1 - fx) * (1 - fy) + 
    TabNoise[INDEX2(iy, ix1)] * fx * (1 - fy) + 
    TabNoise[INDEX2(iy1, ix)] * (1 - fx) * fy + 
    TabNoise[INDEX2(iy1, ix1)] * fx * fy;
}

double noise::NoiseTurb1D( double X, int Octaves )
{
  int frac = 1;
  double val = 0;

  for (int i = 0; i < Octaves; i++ )
  {
    val += Noise1D(X) / frac;
    X = (X + 30.03) * 2;
    frac *= 2;
  }
  return val * ( 1 << (Octaves - 1)) / ((1 << Octaves) - 1);
}

double noise::NoiseTurb2D( double X, double Y, int Octaves )
{
  int frac = 1;
  double val = 0;

  for (int i = 0; i < Octaves; i++ )
  {
    val += Noise2D(X, Y) / frac;
    X = (X + 30.03) * 2;
    Y = (Y + 17.33) * 2;
    frac *= 2;
  }
  return val * ( 1 << (Octaves - 1)) / ((1 << Octaves) - 1);
}
*/
noise::noise( render *R, camera *c )
{
  name = "Noise";
  rnd = R;
  cam = c;
  
  N = new dlgl::noise();
  for (int y = 0; y < GRID_SIZE; y++)
    for (int x = 0; x < GRID_SIZE; x++)
    {
      g->V[y * g->W + x].P = 
          dlgl::vec3(size * x / (GRID_SIZE - 1.0) - size /2.,
                      N->NoiseTurb2D(x * 0.2, y * 0.3, Oct) * 5,
                      size * (1 - y / (GRID_SIZE - 1.0)) - size / 2.);
      //V[y * g->W + x].P = g->V[y * g->W + x].P;
    }
    
  g->AutoNormals();
  g->PrimFromGrid(Prim);
  
  SetMaterial();
  Prim.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3(0, -5, 0)));
 
}

void noise::Delete( void )
{
  delete g;
  delete N;
}

void noise::Draw( dlgl::matr MatrVP )
{
   Prim.Draw(PolygonMode, GL_TRIANGLE_STRIP, MatrVP, rnd, cam);
  //Prim.Draw(GL_LINE, GL_TRIANGLE_STRIP, MatrVP, rnd, cam);
}


void noise::SetMaterial( void )
{
  material m = material::DefMaterial();
  Prim.MtlNo = rnd->resources->AddMaterial(&m) - 1;
}

void noise::Response( void ) 
{
  for (int y = 0; y < GRID_SIZE; y++)
    for (int x = 0; x < GRID_SIZE; x++)
    {
      g->V[y * g->W + x].P.Y = N->NoiseTurb2D(x * 0.2, y * 0.3 + rnd->T.Time, Oct) * 5;
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


void noise::Keyboard( BYTE Keys[256], int IsDown )
{
  /*
   if (! rnd->T.IsPause)
  {
    if (Keys[VK_UP])
      Oct++, Oct &= 7;
    if (Keys[VK_DOWN])
      Oct--, Oct &= 7;
   }
   */
}



