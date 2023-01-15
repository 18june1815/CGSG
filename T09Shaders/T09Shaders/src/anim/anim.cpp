#include "anim.h"


void anim::SetScene( void )
{
  
  *this << new new_sky(rnd, cam);  
  m = new u_mounts(rnd, cam);
  *this << m;
  //*this << new Toyota(rnd, cam);
 // *this << new globe(rnd, cam);
  
  
  *this << new cessna(rnd, cam);
  *this << new Helic(rnd, cam, m);
  //*this << new cow(rnd, cam);
    
  //*this << new sky(rnd, cam);
  *this << new snow(rnd, cam);
  *this << new smoke(rnd, cam);
 // *this << new CenterPoint(rnd, cam);
 
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
  delete cam;
  delete Input;
}

void anim::Init( HWND &hWnd )
{
  rnd = new render();
  rnd->hWnd = hWnd;
  rnd->Init(hWnd);                                                                                                
  
  Input = new input();
  cam = new camera(rnd, Input);
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

  cam->Draw(rnd->MatrView, rnd->MatrVP, rnd->MatrProj);
  cam->Control();

  for (int i = 0; i < NumOfObjects; i++)
    Objects[i]->Draw(rnd->MatrVP);
      
  static char buf[100];
  sprintf(buf, "T08OpenGL, FPS: %.5f", rnd->T.FPS);
  SetWindowText(rnd->hWnd, buf);
  
}


void anim::Keyboard( bool IsDown )
{
  Input->KbdResponse();

  if (Input->Keys['P'] != 0 && IsDown)
    rnd->T.IsPause =! rnd->T.IsPause; 

  for (int i = 0; i < NumOfObjects; i++)
  {
      if (Objects[i]->name == "Helic")
        Objects[i]->Keyboard(Input->Keys);
  }  

  if (Input->Keys['W'] != 0 && IsDown)
  {
    for (int i = 0; i < NumOfObjects; i++)
    {
      if (Objects[i]->PolygonMode == GL_FILL)
        Objects[i]->PolygonMode = GL_LINE;
      else if (Objects[i]->PolygonMode == GL_LINE)
        Objects[i]->PolygonMode = GL_FILL;
    }
  }
}
 

void anim::MouseWheel( WPARAM wParam )
{
  Input->MouseWResponse(wParam);
}

void anim::MouseMove( void )
{
  Input->MouseClickResponse();
}



anim & anim::operator<<( object *Obj )
{
  if (NumOfObjects < MaxNumOfObjects)
    Objects.push_back(Obj);
  NumOfObjects++;
  return *this;
} /* End of 'operator<<' function */


