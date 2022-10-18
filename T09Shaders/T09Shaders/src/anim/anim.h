#ifndef __ANIM_H_
#define __ANIM_H_

#include "rnd/rnd.h"
#include <vector>
#include "units/Units.h"

class anim
{
public:
  static const int MaxNumOfObjects = 100000;
  std::vector<object *> Objects; 
  int NumOfObjects = 0;

   anim( void )
   {
   }
  ~anim( void );
 
  void Init( HWND hWnd, WPARAM wp, LPARAM lp );
  void Resize( int W, int H);
  void CopyFrame( void );
  void Draw( void );
  void MouseWheel( WPARAM wParam );
  void MouseMove( WPARAM wParam, LPARAM lParam );
  anim & operator<<( object *Obj );
  void SetScene( void );
};
#endif /* __ANIM_H_ */