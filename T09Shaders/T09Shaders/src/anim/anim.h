#ifndef __ANIM_H_
#define __ANIM_H_

#include "rnd/rnd.h"
#include <vector>
#include "units/Units.h"
#include "rnd/Input.h"
#include "rnd/camera.h"
#include "rnd/res/rndfnt.h"


class anim
{
public:
  static const int MaxNumOfObjects = 100000;
  std::vector<object *> Objects; 
  int NumOfObjects = 0;

  render *rnd;
  u_mounts *m;
  Helic *Hel;
  camera *cam;
  font *Fnt;

  input *Input; 

  int IsCollision = 0;
  dlgl::vec3 CollisionPoint;

  int PolygonMode = GL_FILL;
  anim( void )
  {
  }
  ~anim( void );
 
 
  void Init( HWND &hWnd );
  void Resize( int W, int H);
  void CopyFrame( void );
  void Draw( void );
  void MouseWheel( WPARAM wParam );
  void MouseMove( void );
  void Keyboard( bool IsDown );
  anim & operator<<( object *Obj );
  void SetScene( void );
  int FindObject( std::string name );
};
#endif /* __ANIM_H_ */