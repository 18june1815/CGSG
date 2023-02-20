#ifndef __UNITS_H_
#define __UNITS_H_

#include <vector>                
#include "anim/rnd/prim.h"
#include "anim/rnd/prims.h"
#include "anim/rnd/camera.h"

#define MAX_FLAKES 300
#define MAX_FIRE 3
#define MAX_TREES 3

class object
{
public:
  render *rnd;  
  camera *cam;
  std::string name;
  int PolygonMode = GL_FILL;

  virtual void Draw( dlgl::matr MatrVP )
  {
  } /* End of 'Render' function */

  virtual void Response( void )
  {
  } /* End of 'Response' function */

  virtual void Keyboard( BYTE Keys[256], int IsDown )
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
  globe( render *R, camera *cam );

  void GlobeSet( void );
  void Response( void ) override;
  void SetMaterial( void );
  int SetTexture( void );
  void Draw( dlgl::matr MatrVP  ) override;
};

class u_mounts: public object
{
public:
  float size = 300, h = 30;
  prim Prim;
  HBITMAP hBm;
  u_mounts( render *R, camera *cam );
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
  void Response( void ) override;
  void Delete( void ) override;
  float GetHeight( dlgl::vec3 P);
};

// Objects from .obj files
class cow : public object
{
public:
  prim Prim;
  prims Prims;
  cow ( render *R, camera *cam );  
  bool Load( const char *FileName ); 
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
  int SetTexture( void );
  void Delete( void ) override;
};


class Toyota : public object
{
public:
  prim Prim;
  prims Prims;
  u_mounts *Mounts;
  dlgl::vec3 Pos{0, 0, 0}, Dir, OldDir, R;
  dlgl::matr Initial, Mcur = dlgl::matr::Identity();
  float Speed = 0, Angle = 0;
  float BL, BW; // base length, base width
  float dA;
  int Sign = 1;
    dlgl::vec3 WheelCurPos[4], WheelCentr[4], CurPos;
  int IsRotation = 0;
  

  Toyota ( render *R, camera *cam, u_mounts *m );  
  bool Load( const char *FileName ); 
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
  int SetTexture( void );
  void Delete( void ) override;
  void Response( void ) override;
  void Keyboard( BYTE Keys[256], int IsDown ) override;
};



class cessna : public object
{
public:
  prim Prim;
  prims Prims;
  cessna ( render *R, camera *cam );  
  bool Load( const char *FileName ); 
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
  int SetTexture( void );
  void Delete( void ) override;
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
    CollisionPoint{0, 0, 0},

    Dir{0., 0., 1.},
    OldDir{0., 0., 1.};

  dlgl::matr Scale = dlgl::matr::Scale(Sc);
  int Sign = 1, IsCollision = 0;
  float 
    CourseSpeed = 0, Speed = 0, xAngle = 0;

  u_mounts *Mounts;

  prim Prim;
  prims Prims;
  Helic ( render *R, camera *cam );  
  Helic ( render *R, camera *cam, u_mounts *mounts );  
  bool Load( const char *FileName ); 
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
  void Response( void ) override;
  void Keyboard( BYTE Keys[256], int IsDown ) override;
  void Delete( void ) override;
  void BladesRotationX( void );
  void BladesRotationY( void );
  void Collisions( void );
  void GetCollision( int isCollision, dlgl::vec3 collisionPoint);
};


class sky: public object
{
public:
  prim Prim;
  sky( render *R, camera *cam );
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
};


class CenterPoint: public object
{
public:
  prim Prim;
  CenterPoint( render *R, camera *cam );
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
};

class snow: public object
{
public:
  prim Prim;
  vertex Flakes[MAX_FLAKES];

  snow( render *R, camera *cam );
  void Draw( dlgl::matr MatrVP  ) override;
  void Response( void ) override;
};

class smoke: public object
{
public:
  prim Prim;

  smoke( render *R, camera *cam );
  void Draw( dlgl::matr MatrVP  ) override;
};

class new_sky: public object
{
public:
  prim Prim;

  new_sky( render *R, camera *cam );
  void Draw( dlgl::matr MatrVP  ) override;
};

class CollisionFire: public object
{
public:
  prim Prim;
  vertex Loc[MAX_FIRE];
  int dTime;
  int IsFire = 0;

  CollisionFire( render *R, camera *cam );
  void Draw( dlgl::matr MatrVP  ) override;
  void Response( void ) override;
};


class grass: public object
{
public:
  prim Prim;
  
  grass( render *R, camera *cam );
  void Draw( dlgl::matr MatrVP  ) override;
  void Response( void ) override;

};

class tess: public object
{
public:
  prim Prim;
  
  tess( render *R, camera *cam );
  void Draw( dlgl::matr MatrVP  ) override;
  void Response( void ) override;
};

class trees : public object
{
public:
  prim Prim;
  prims Prims;
  dlgl::vec3
    pos[MAX_TREES],
    scale[MAX_TREES];

  u_mounts *Mounts;
  trees ( render *R, camera *cam, u_mounts *mounts );  
  bool Load( const char *FileName ); 
  void SetMaterial( void );
  void Draw( dlgl::matr MatrVP  ) override;
  int SetTexture( void );
  void Delete( void ) override;
};


#endif /* __UNITS_H_ */
