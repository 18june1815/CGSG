#include "Units.h"

Toyota::Toyota( render *R )
{
  name = "Toyota";
  rnd = R;
  //Prim.MtlNo = 0;
  //Prim.Load("bin/models/Toyota.obj");
  //Prim.LoadNew("bin/models/Toyota.obj");
  
  Prims.LoadG3DM("bin/models/Toyota.g3dm");
  Prims.SetWorldTransormation(dlgl::matr::Scale(dlgl::vec3{0.5, 0.5, 0.5}));
  //SetMaterial();
}

void Toyota::Delete( void )
{
  Prims.Delete();
}

void Toyota::SetMaterial( void )
{
  /*
  material m = material::DefMaterial();
  m.Name = "Toyota";

  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
  */
}

void Toyota::Draw( dlgl::matr MatrVP  ) 
{
  for (int i = 0; i < Prims.NofElements; i++)
  {
    Prims.primitives[i]->Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd);
  }
}

