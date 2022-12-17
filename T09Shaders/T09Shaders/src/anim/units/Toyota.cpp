#include "Units.h"

Toyota::Toyota( render *R, camera *c )
{
  name = "Toyota";
  rnd = R;
  cam = c;
  
  Prims.rnd = rnd;
  Prims.cam = cam;
  Prims.LoadG3DM("bin/models/Toyota.g3dm");

  
  Prims.SetWorldTransormation(dlgl::matr::RotateX(90));
  Prims.SetWorldTransormation(dlgl::matr::RotateY(-45));
  Prims.SetWorldTransormation(dlgl::matr::Scale(dlgl::vec3{0.7, 0.7, 0.7}));
  //Prims.SetWorldTransormation(dlgl::matr::Scale(dlgl::vec3{0.2, 0.2, 0.2}));
  Prims.SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3{0, -3, -5}));
}

void Toyota::Delete( void )
{
  Prims.Delete();
}


void Toyota::Draw( dlgl::matr MatrVP  ) 
{
  Prims.Draw(MatrVP);
}

