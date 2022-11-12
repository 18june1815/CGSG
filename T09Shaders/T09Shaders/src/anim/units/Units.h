#ifndef __UNITS_H_
#define __UNITS_H_

#include <vector>
                
//#include "def.h"
#include "anim/rnd/prim.h"

class object
{
public:
  render *rnd;  
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


// Objects from .obj files
class cow : public object
{
public:
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
    Pos{0.0, 0., 0.},
    dPos{0.0, 0., 0.};

  float CourseSpeed = 0, Speed = 0, Course = 0;

  prim Prim;
  Helic ( render *R );  
  bool Load( const char *FileName ); 
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
  void Response( void ) override;
  void Keyboard( WPARAM wParam ) override;
};


class sky: public object
{
public:
  prim Prim;
  sky( render *R );
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
};

class u_mounts: public object
{
public:
  prim Prim;
  u_mounts( render *R );
  ~u_mounts();
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
  void Response( void ) override;
};
#endif /* __UNITS_H_ */
