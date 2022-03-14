#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileExit = new wxMenuItem(nullptr, wxID_EXIT, "Exit\tCtrl+Q");

  file = new wxMenu();
  file->Append(fileExit);

  viewShowControls = new wxMenuItem(nullptr, SHOWCONTROLS, "Show Controls");

  view = new wxMenu();
  view->Append(viewShowControls);

  Append(file, "File");
  Append(view, "View");
}

