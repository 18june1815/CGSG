#ifndef __timer_h_
#define __timer_h_

#include "rnd.h"

namespace rnd
{
  class timer
  {
  public:
    UINT64 
      StartTime, 
      OldTime,
      OldTimeFPS,
      PauseTime, 
      TimePerSec,
      time,
      FrameCounter;

    double GlobalTime, GlobalDeltaTime, Time, DeltaTime, FPS;
    bool IsPause = false;

    timer( void )
    {
      LARGE_INTEGER t;
      
      QueryPerformanceFrequency(&t);
      TimePerSec = t.QuadPart;


      QueryPerformanceCounter(&t);
      time = t.QuadPart;

      StartTime = OldTime = OldTimeFPS = t.QuadPart;
      FrameCounter = 0;
      IsPause = FALSE;
      FPS = 10.0;
      PauseTime = 0;
    }
    void Response( void )
    {
      LARGE_INTEGER t;
    
      QueryPerformanceCounter(&t);
    
      /* Global Time */
      GlobalTime = (double)(t.QuadPart - StartTime) / TimePerSec;
      GlobalDeltaTime = (double)(t.QuadPart - OldTime) / TimePerSec;
    
      /* Time with pause */
      if (IsPause)
      {
        DeltaTime = 0;
        PauseTime += t.QuadPart - OldTime;
      }
      else
      {
        DeltaTime = GlobalDeltaTime;
        Time = (double)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
      }
    
      /* FPS */
      FrameCounter++;
      if ((t.QuadPart - OldTimeFPS) > TimePerSec)
      {
        FPS = FrameCounter * TimePerSec / (double)(t.QuadPart - OldTimeFPS);
        OldTimeFPS = t.QuadPart;
        FrameCounter = 0;
      }
      OldTime = t.QuadPart;
    }
    
    
  };
}


#endif /* __timer_h_ */