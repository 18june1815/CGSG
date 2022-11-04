#ifndef __UNITS_H_
#define __UNITS_H_

#include <vector>
                
//#include "def.h"
#include "anim/prim.h"

class object
{
public:
  
  virtual void Draw( dlgl::matr MatrVP )
  {
  } /* End of 'Render' function */

  virtual void Response( void )
  {
  } /* End of 'Response' function */

  virtual void Keyboard( void )
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
  globe( void );

  void GlobeSet( void );
  void Response( void ) override;
  void SetMaterial( void );
  int SetTexture( void );
  void Draw( dlgl::matr MatrVP  ) override;
};


// Objects from .obj files
class objprim : public object
{
public:
  prim Prim;
  objprim ( const char *FN );  
  bool Load( const char *FileName ); 
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
  int SetTexture( void );
};



class u_grid: public object
{
public:
  prim Prim;
  u_grid();
  ~u_grid();
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
};




class u_mounts: public object
{
public:
  prim Prim;
  u_mounts();
  ~u_mounts();
  void SetMaterial( void );
  int SetTexture( void );
  void Draw( dlgl::matr MatrVP  ) override;
  void Response( void ) override;
};
#endif /* __UNITS_H_ */
