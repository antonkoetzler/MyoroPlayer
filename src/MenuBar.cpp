#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileQuit = new wxMenuItem(nullptr, wxID_EXIT, "Quit\tCtrl+Q");
  file = new wxMenu();
  file->Append(fileQuit);

  Append(file, "File");
}
