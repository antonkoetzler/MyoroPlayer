#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileMenu = new wxMenu();

  fileExit = new wxMenuItem(
    nullptr,
    wxID_EXIT,
    "Quit\tCtrl+Q",
    "Closes MyoroPlayer",
    wxITEM_NORMAL,
    nullptr
  );
  fileMenu->Append(fileExit);



  helpMenu = new wxMenu();

  helpAbout = new wxMenuItem(
    nullptr,
    wxID_ANY,
    "About MyoroPlayer",
    wxEmptyString,
    wxITEM_NORMAL,
    nullptr
  );
  helpMenu->Append(helpAbout);



  Append(fileMenu, "File");
  Append(helpMenu, "Help");
}
