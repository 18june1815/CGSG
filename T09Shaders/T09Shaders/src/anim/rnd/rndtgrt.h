#ifndef __RNDTGRT_H_
#define __RNDTGRT_H_

#include "res/rndres.h"

#define N_TARGETS 6

class tgrt
{
public:
  GLuint TargetTexId[N_TARGETS];
  int 
    TargetShd,
    TargetShdLightAmbient,
    TargetShdLightDirectional,
    TargetShdLightPoint;
  GLuint TargetFBO, RndTarget, TargetRndBuf;
  int W, H;
  res *resources;

  void Init( res *r, int w, int h);
  void Resize(int w, int h);
  void Free( void );
  void Create( void );
  void Close( void );
  void Start( void );     
  void End( UINT64 Time, dlgl::vec3 CamLoc );
};

#endif /*__RNDTGRT_H_*/