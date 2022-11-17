#include "Units.h"

cow::cow( render *R )
{
  rnd = R;
  Prim.MtlNo = 0;
  //Prim.Load("bin/models/cow.obj");
  Prim.LoadNew("bin/models/cow.obj");
  Prim.SetWorldTransormation(dlgl::matr::Scale({15, 15, 15}));
  //SetMaterial();
}


void cow::SetMaterial( void )
{
  material m = material::DefMaterial();
  m.Name = "cow";

  Prim.MtlNo = rnd->resources.AddMaterial(&m) - 1;
  
}

void cow::Draw( dlgl::matr MatrVP  ) 
{
  Prim.Draw(GL_FILL, GL_TRIANGLES, MatrVP, rnd);
}
