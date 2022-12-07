#include "Units.h"

cow::cow( render *R )
{
  name = "Cow";
  rnd = R;
  //Prim.MtlNo = 0;
  //Prim.Load("bin/models/cow.obj");
  //Prim.LoadNew("bin/models/cow.obj");
  
  Prims.LoadG3DM("bin/models/cow.g3dm");
  Prims.SetWorldTransormation(dlgl::matr::Scale(dlgl::vec3{0.5, 0.5, 0.5}));
  //SetMaterial();
}

void cow::Delete( void )
{
  Prims.Delete();
}

void cow::SetMaterial( void )
{
  /*
  material m = material::DefMaterial();
  m.Name = "cow";

  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
  */
}

void cow::Draw( dlgl::matr MatrVP  ) 
{
  for (int i = 0; i < Prims.NofElements; i++)
  {
    Prims.primitives[i]->Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd);
  }
}

