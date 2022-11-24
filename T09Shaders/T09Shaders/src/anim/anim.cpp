#include "anim.h"


void anim::SetScene( void )
{
  //m = new u_mounts(rnd);
  //*this << m;
  *this << new globe(rnd);                              
  
  *this << new CenterPoint(rnd);                                                     
  *this << new Helic(rnd);                                                     
  //*this << new cow(rnd);
  /*for (int i = 0; i < 5; i++ )
    *this << new globe(rnd);                              
  */
  //*this << new sky(rnd);
  //
}

anim::~anim( void )
{
  //delete m;
  for (int i = 0; i < NumOfObjects; i++)
  {
    Objects[i]->Delete();
    delete Objects[i];
  }
  
  rnd->Close();
  delete rnd;
}
void anim::Init( HWND &hWnd )
{
  rnd = new render();
  rnd->hWnd = hWnd;
  rnd->Init(hWnd);

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
  for (int i = 0; i < NumOfObjects; i++)
    Objects[i]->Response();
    
  rnd->Start();
  rnd->cam.Draw(rnd->MatrView, rnd->MatrVP, rnd->MatrProj);
  for (int i = 0; i < NumOfObjects; i++)
    Objects[i]->Draw(rnd->MatrVP);
      
  static char buf[100];
  sprintf(buf, "T08OpenGL, FPS: %.5f", rnd->T.FPS);
  SetWindowText(rnd->hWnd, buf);
  
}


void anim::Keyboard( WPARAM wParam )
{
  for (int i = 0; i < NumOfObjects; i++)
  {
    bool a = Objects[i]->name == "Helic";
      if (Objects[i]->name == "Helic")
        Objects[i]->Keyboard(wParam);
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


