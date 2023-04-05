#include "Units.h"                                                         

cessna::cessna( render *R, camera *c )
{
  name = "cessna";
  rnd = R;
  cam = c;
  
  Prims.rnd = rnd;
  Prims.cam = cam;


  Prims.LoadG3DM("bin/models/cessna172.g3dm");
  //Prims.LoadG3DM("bin/models/Mi28.g3dm");

  for (int i = 0; i < Prims.NofElements; i++)
  {
    int MtlNo = Prims.primitives[i]->MtlNo;
 
    material *mtl = &(rnd->resources->mtl[MtlNo]);
    mtl->Tex[0] = -1;
    mtl->Ka = dlgl::vec3(0.7, 0.7, 0.8);
  }

  Prims.SetWorldTransormation(dlgl::matr::RotateX(90));
  Prims.SetWorldTransormation(dlgl::matr::RotateY(-45));
  Prims.SetWorldTransormation(dlgl::matr::Scale(dlgl::vec3{0.4, 0.4, 0.4}));
  Prims.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3{0, -3, -5}));
}

void cessna::Delete( void )
{
  Prims.Delete();
}


void cessna::Draw( dlgl::matr MatrVP  ) 
{
  
  Prims.Draw(MatrVP);
}

