#ifndef __def_h_
#define __def_h_

#pragma warning(disable: 4244 4013 4018 4115 4761 4305)
#pragma warning(1: 4087 4130 4189 4296 4701 4706 4702)


#include <windows.h>
//#pragma comment(lib, "user32.lib")
//#pragma comment(lib, "gdi32.lib")


/* Debug memory allocation support */ 
#if !defined(NDEBUG)
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
     _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

/* class for debug memory allocation support */
static class __Dummy
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    //_CrtSetBreakAlloc(281); -- use for memory leak check
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __ooppss;
#endif

/* STL includes */
#include <string>
#include <iostream>
#include <fstream>

#include <ctime>

#include "mth/mth.h"


/* 64 bit integer data type */
typedef long long INT64;
typedef unsigned long long UINT64;

#endif /*__def_h_*/
