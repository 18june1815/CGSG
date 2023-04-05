#include "anim.h"


void anim::SetScene( void )
{ 
  //*this << new CenterPoint(rnd, cam);
  
  *this << new new_sky(rnd, cam);  
  //m = new u_mounts(rnd, cam);
  //*this << m;
  //
  //*this << new Toyota(rnd, cam, m);
  //*this << new trees(rnd, cam, m);
 // *this << new globe(rnd, cam);
  
  
 // *this << new cessna(rnd, cam);
 //*this << new Helic(rnd, cam, m);
  //Hel = new Helic(rnd, cam, m);
  //*this << Hel;
  *this << new cow(rnd, cam);
    
  //*this << new sky(rnd, cam);
 // *this << new snow(rnd, cam);
  //*this << new smoke(rnd, cam);
 // *this << new CollisionFire(rnd, cam);  
 
  //*this << new grass(rnd, cam);
  //*this << new tess(rnd, cam);
  
  //*this << new tess_sphere(rnd, cam);
  //Shadow = new shadow(rnd, cam, Objects);
  //*this << new debug(rnd, cam);
  *this << new noise(rnd, cam);
  Fnt = new font(rnd, cam);
}

anim::~anim( void )
{ 
  Fnt->Delete();
  delete Fnt;

  for (int i = 0; i < NumOfObjects; i++)
  {
    Objects[i]->Delete();

    if (Objects[i]->name != "Mounts" && Objects[i]->name != "Helic")
      delete Objects[i];
  }

  if (GetObject("Helic") != NULL)
    delete Hel;
  delete m;
  //delete Shadow;

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
    if (FindObject("Helic") != -1)
    {
      IsCollision = Hel->IsCollision;
      CollisionPoint = Hel->CollisionPoint;
      int FireN =  FindObject("CollisionFire");
      if (FireN != -1)
      {
        CollisionFire *Fire = static_cast<CollisionFire*>(Objects[FireN]);
    
        if (IsCollision == 1)
        {
          Fire->IsFire = 1;
          Fire->Loc[0].P = CollisionPoint;
        }
        else 
          Fire->IsFire = 0;
      }
    }
    
     
    for (int i = 0; i < NumOfObjects; i++)
      Objects[i]->Response();
  } 

  //Shadow->Response(rnd->MatrVP);



  cam->Draw(rnd->MatrView, rnd->MatrVP, rnd->MatrProj);
  cam->Control();
  
  rnd->Start();
  char buf[300];
  sprintf(buf, "T08OpenGL, FPS: %.5f", rnd->T.FPS);
  Fnt->Draw(buf, dlgl::vec3(-rnd->FrameW / 2 + 10, rnd->FrameH / 2 - 20, 0), 20, GL_FILL);
  SetWindowText(rnd->hWnd, buf);

  
  for (int i = 0; i < NumOfObjects; i++)
    Objects[i]->Draw(rnd->MatrVP);

  rnd->End(cam->Loc);

  //Shadow->Draw(rnd->MatrVP);
}


void anim::Keyboard( bool IsDown )
{
  Input->KbdResponse();

  if (Input->Keys['P'] != 0 && IsDown)
    rnd->T.IsPause =! rnd->T.IsPause; 

  if (Input->Keys['C'] != 0 && IsDown)
  {
    if (GetObject("Helic") != NULL && GetObject("Toyota") != NULL)
    {
      GetObject("Helic")->IsActive = !GetObject("Helic")->IsActive;
      GetObject("Toyota")->IsActive = !GetObject("Toyota")->IsActive;
    }
  }

  for (int i = 0; i < NumOfObjects; i++)
  {
    if (Objects[i]->name == "Helic" && Objects[i]->IsActive)
      Objects[i]->Keyboard(Input->Keys, IsDown);
    if (Objects[i]->name == "Toyota" && Objects[i]->IsActive)
      Objects[i]->Keyboard(Input->Keys, IsDown);

    if (Objects[i]->name == "Noise")
      Objects[i]->Keyboard(Input->Keys, IsDown);
  }  

  if (Input->Keys['W'] != 0 && IsDown)
  {
    for (int i = 0; i < NumOfObjects; i++)
    {
      if (Objects[i]->PolygonMode == GL_FILL)
      {
          Objects[i]->PolygonMode = GL_LINE;
          PolygonMode = GL_LINE;
      }
      
      else if (Objects[i]->PolygonMode == GL_LINE)
      {
          Objects[i]->PolygonMode = GL_FILL;
          PolygonMode = GL_FILL;
      }
      
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



int anim::FindObject( std::string name )
{
  for (int i = 0; i < NumOfObjects; i++)
  {
    if (Objects[i]->name == name)
    return i;
  } 
  return -1;
}

object* anim::GetObject( std::string name )
{
  for (int i = 0; i < NumOfObjects; i++)
  {
    if (Objects[i]->name == name)
    return Objects[i];
  } 
  return NULL;
}
anim & anim::operator<<( object *Obj )
{
  if (NumOfObjects < MaxNumOfObjects)
    Objects.push_back(Obj);
  NumOfObjects++;
  return *this;
} /* End of 'operator<<' function */


