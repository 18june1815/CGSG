#ifndef __UNITS_H_
#define __UNITS_H_

#include <vector>                
#include "anim/rnd/prim.h"
#include "anim/rnd/prims.h"


class object
{
public:
  render *rnd;  
  std::string name;
  virtual void Draw( dlgl::matr MatrVP )
  {
  } /* End of 'Render' function */

  virtual void Response( void )
  {
  } /* End of 'Response' function */

  virtual void Keyboard( WPARAM wParam )
  {
  } /* End of 'Keyboard' function */

  virtual void MouseWheel( void )
  {
  } /* End of 'MouseWheel' function */

  virtual void MouseMove( void )
  {
  } /* End of 'MouseMove' function */

  virtual void Delete( void )
  {
  }
}; /* End of 'object' class */


// Globe
class globe : public object
{
  prim Prim;
  static const int GLOBE_H = 30, GLOBE_W = 30;
  dlgl::vec3 Geom[GLOBE_H][GLOBE_W];
  dlgl::vec3 pos;
  void GeomSet( double R );

public:
  globe( render *R );

  void GlobeSet( void );
  void Response( void ) override;
  void SetMaterial( void );
  int SetTexture( void );
  void Draw( dlgl::matr MatrVP  ) override;
};

class u_mounts: public object
{
public:
  prim Prim;
  HBITMAP hBm;
  //std::vector<dlgl::vec3> Pmounts;
  u_mounts( render *R );
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
  void Response( void ) override;
  void Delete( void ) override;
};

// Objects from .obj files
class cow : public object
{
public:
  std::string name = "Cow";
  prim Prim;
  cow ( render *R );  
  bool Load( const char *FileName ); 
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
  int SetTexture( void );
};



class Helic : public object
{
public:
  dlgl::vec3 
    Sc{0.05, 0.05, 0.05},
    Pos{0., 0., 0.},
    dPos{0., 0., 0.},
    Angle{0, 0, 0},
    dAngle{0, 0, 0},

    Dir{0., 0., 1.},
    OldDir{0., 0., 1.};

  dlgl::matr Scale = dlgl::matr::Scale(Sc);
  int Sign = 1;
  float 
    CourseSpeed = 0, Speed = 0, xAngle = 0;

  //u_mounts *Mounts;

  prim Prim;
  prims Prims;
  Helic ( render *R );  
  Helic ( render *R, u_mounts *mounts );  
  bool Load( const char *FileName ); 
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
  void Response( void ) override;
  void Keyboard( WPARAM wParam ) override;
  void Delete( void ) override;
  void BladesRotationX( void );
  void BladesRotationY( void );
  //void Collisions( void );
};


class sky: public object
{
public:
  prim Prim;
  sky( render *R );
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
};


class CenterPoint: public object
{
public:
  prim Prim;
  CenterPoint( render *R );
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
};


#endif /* __UNITS_H_ */
