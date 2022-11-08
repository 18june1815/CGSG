#include <Windows.h>
#include "dl1.h"


/* Window class name */
#define WND_CLASS_NAME "My Window Class Name"

/* Forward declaration */
LRESULT CALLBACK WinFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

/* The main program function */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR* CmdLine, INT CmdShow)
{
  HWND hWnd;
  MSG msg;
  WNDCLASS wc;

  /* Fill window class structure */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpszClassName = WND_CLASS_NAME;
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = WinFunc;


  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error regoister window class", "Error", MB_OK | MB_ICONERROR);
    return 0;
  }

  /* Window creation */
   hWnd = CreateWindow(WND_CLASS_NAME, "ANIM",
    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
    /* CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, */
    CW_USEDEFAULT, CW_USEDEFAULT, 550, 400,
    NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, CmdShow);


 
  /* Message loop */
  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);

  return 30;
} /* End of 'WinMain' function */



/* Main window handle function */
LRESULT CALLBACK WinFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  MINMAXINFO* minmax;
  PAINTSTRUCT ps;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO*)lParam;
    minmax->ptMinTrackSize.x = 400;
    minmax->ptMinTrackSize.y = 400;
    return 0;
  case WM_CREATE: 
    //MyAnim.rnd->hWnd = hWnd;
    MyAnim.Init(hWnd);
   return 0;
  case WM_SIZE:
    MyAnim.Resize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(MyAnim.rnd->hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(MyAnim.rnd->hWnd, WM_CLOSE, 0, 0);
    return 0;
  case WM_TIMER:
    MyAnim.Draw();
    MyAnim.CopyFrame();
    PostMessage(MyAnim.rnd->hWnd, WM_PAINT, 0, 0);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_LBUTTONDOWN:
    return 0;
   case WM_MOUSEWHEEL:
     MyAnim.MouseWheel(wParam);
  case WM_MOUSEMOVE:
    if (wParam & MK_LBUTTON)
     MyAnim.MouseMove(wParam, lParam);
    return 0;
 
  case WM_PAINT:
    MyAnim.rnd->hDC = BeginPaint(MyAnim.rnd->hWnd, &ps);
    MyAnim.CopyFrame();
    EndPaint(MyAnim.rnd->hWnd, &ps); 
    return 0;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure you want to close window?", "Close",
      MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    return 0;
  case WM_DESTROY:
    PostMessage(MyAnim.rnd->hWnd, WM_QUIT, 0, 0);
    KillTimer(MyAnim.rnd->hWnd, 30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */
