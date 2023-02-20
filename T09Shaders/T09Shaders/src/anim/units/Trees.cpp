#include "Units.h"                                                         

trees::trees( render *R, camera *c, u_mounts *mounts )
{
  name = "trees";
  rnd = R;
  cam = c;
  Mounts = mounts;

  Prims.rnd = rnd;
  Prims.cam = cam;
  Prims.LoadG3DM("bin/models/Tree1.g3dm");

  for (int i = 0; i < MAX_TREES; i++)
  {
    float Rx = 15 * (float) rand()/RAND_MAX - 8;
    float Ry = 15 * (float) rand()/RAND_MAX - 8;
    pos[i] = dlgl::vec3(3 * Rx, 0, 3 * Ry);     
    pos[i].Y = Mounts->GetHeight(pos[i]) + 3;

    float Rs = 1.5 * (float) rand()/RAND_MAX + 0.05;
    scale[i] = dlgl::vec3(Rs, Rs, Rs);
  }
  
  Prims.SetWorldTransormation(dlgl::matr::Scale(dlgl::vec3{0.1, 0.1, 0.1}));
  Prims.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3{0, -3, -5}));
}

void trees::Delete( void )
{
  Prims.Delete();
}


void trees::Draw( dlgl::matr MatrVP  ) 
{
  for (int i = 0; i < MAX_TREES; i++)
  {
    dlgl::matr M;
    //M = dlgl::matr::Scale(scale[i]) * dlgl::matr::Translate(pos[i]);
    M = dlgl::matr::Translate(pos[i]);
    Prims.Draw(M * MatrVP);
  }
  
}

