#include "App.h"

IMPLEMENT_APP(App);

bool App::OnInit()
{
  // HWND hWnd = GetConsoleWindow();
  // ShowWindow(hWnd, SW_HIDE);
  window = new Frame();
  window->Show(true);
  return true;
}

