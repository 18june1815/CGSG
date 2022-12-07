#include "anim.h"


void anim::SetScene( void )
{
  //m = new u_mounts(rnd);
  //*this << m;
  //*this << new u_mounts(rnd);
  *this << new Toyota(rnd);
  *this << new globe(rnd);
  
  //*this << new CenterPoint(rnd);
  //*this << new Helic(rnd, m);
  //*this << new cow(rnd);
  /*for (int i = 0; i < 5; i++ )
    *this << new globe(rnd);
  */
  //*this << new sky(rnd);
  //
}

anim::~anim( void )
{ 
  for (int i = 0; i < NumOfObjects; i++)
  {
    if (Objects[i]->name != "Mounts")
    {
      Objects[i]->Delete();
      delete Objects[i];
    }
  }
  delete m;
  
  rnd->Close();
  delete rnd;
}
void anim::Init( HWND &hWnd )
{
  rnd = new render();
  rnd->hWnd = hWnd;
  rnd->Init(hWnd);                                                                                                
  
  SetKeys();
  SetScene();  
}

void anim::Resize( int W, int H)
{
  rnd->Resize(W, H);
}

void anim::CopyFrame( void )
{   
  rnd->CopyFrame();  
}

void anim::Draw( void )
{
  if (!rnd->T.IsPause)
  {
    for (int i = 0; i < NumOfObjects; i++)
      Objects[i]->Response();
  } 
  rnd->Start();

  rnd->cam.Draw(rnd->MatrView, rnd->MatrVP, rnd->MatrProj);
  for (int i = 0; i < NumOfObjects; i++)
    Objects[i]->Draw(rnd->MatrVP);
      
  static char buf[100];
  sprintf(buf, "T08OpenGL, FPS: %.5f", rnd->T.FPS);
  SetWindowText(rnd->hWnd, buf);
  
}

void anim::SetKeys( void )
{
  Keys[VK_RIGHT] = Keys[VK_LEFT] = 1;
}


void anim::Keyboard( WPARAM wParam )
{
  for (int i = 0; i < NumOfObjects; i++)
  {
    if (Objects[i]->name == "Helic")
      Objects[i]->Keyboard(wParam);
  }
  switch (wParam)
  {
  case VK_RIGHT:
    Keys[VK_RIGHT] *= -1;
    break;

  case VK_LEFT:
    Keys[VK_RIGHT] *= -1;  
    break;
  case 'P':
    rnd->T.IsPause = !rnd->T.IsPause;
    break;
     /*
  case VK_UP:
    Speed += 0.001;
    break;

  case VK_DOWN:
    if (Speed > 0)
      Speed -= 0.001;
    break;

  case VK_PRIOR:
    dPos.Y += 0.1;
    break;

  case VK_NEXT:
    dPos.Y -= 0.1;
    break;

  case VK_SPACE:
    Speed = 0;
    break;
    */
    }
}
 

void anim::MouseWheel( WPARAM wParam )
{
/*  rnd->cam.MouseWheel(wParam);
  for (int i = 0; i < NumOfObjects; i++)
    Objects[i]->MouseWheel();
    */
}

void anim::MouseMove( WPARAM wParam, LPARAM lParam )
{
/*  rnd->cam.MouseMove(wParam, lParam, rnd->FrameW, rnd->FrameH, rnd->MatrView);
  for (int i = 0; i < NumOfObjects; i++)
    Objects[i]->MouseMove();
*/
}



anim & anim::operator<<( object *Obj )
{
  if (NumOfObjects < MaxNumOfObjects)
    Objects.push_back(Obj);
  NumOfObjects++;
  return *this;
} /* End of 'operator<<' function */


