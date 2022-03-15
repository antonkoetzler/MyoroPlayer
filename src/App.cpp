#include "App.h"

IMPLEMENT_APP(App);

bool App::OnInit()
{
  window = new Frame();
  window->Show(true);
  return true;
}

