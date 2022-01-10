#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileMenu = new wxMenu();
  fileExit = new wxMenuItem(
    nullptr,
    wxID_EXIT,
    "Exit\tCtrl+Q",
    wxEmptyString,
    wxITEM_NORMAL,
    nullptr
  );
  fileMenu->Append(fileExit);
  Append(fileMenu, "File");

  helpMenu = new wxMenu();
  helpAbout = new wxMenuItem(
    nullptr,
    wxID_ABOUT,
    "About MyoroPlayer",
    wxEmptyString,
    wxITEM_NORMAL,
    nullptr
  );
  helpMenu->Append(helpAbout);
  Append(helpMenu, "Help");
}
