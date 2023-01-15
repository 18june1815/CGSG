#include "Units.h"

cow::cow( render *R, camera *c )
{
  name = "Cow";
  rnd = R;
  cam = c;
  //Prim.MtlNo = 0;
  //Prim.Load("bin/models/cow.obj");
  //Prim.LoadNew("bin/models/cow.obj");
  
  //Prims.LoadG3DM("bin/models/cow.g3dm");
  Prim.SetWorldTransormation(dlgl::matr::Scale(dlgl::vec3{50, 50, 50}));
  //SetMaterial();
}

void cow::Delete( void )
{
  //Prims.Delete();
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
  Prim.Draw(PolygonMode, GL_TRIANGLES, MatrVP, rnd, cam);

}

