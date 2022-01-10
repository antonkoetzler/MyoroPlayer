#include "App.h"

IMPLEMENT_APP(App);

bool App::OnInit()
{
  mainWindow = new Frame();
  mainWindow->Show(true);

  return true;
}
