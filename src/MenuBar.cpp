#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileExit = new wxMenuItem(
    nullptr,
    wxID_EXIT,
    "Exit MyoroPlayer\tCtrl+Q"
  );

  file = new wxMenu();
  file->Append(fileExit);

  Append(file, "File");
}
