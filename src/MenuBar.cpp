#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileSetDirectory = new wxMenuItem(
    nullptr,
    SETDIR,
    "Set Directory\tCtrl+W"
  );

  fileExit = new wxMenuItem(
    nullptr,
    wxID_EXIT,
    "Exit MyoroPlayer\tCtrl+Q"
  );

  file = new wxMenu();
  file->Append(fileSetDirectory);
  file->Append(fileExit);

  helpAbout = new wxMenuItem(
    nullptr,
    ABOUT,
    "About MyoroPlayer"
  );

  help = new wxMenu();
  help->Append(helpAbout);

  Append(file, "File");
  Append(help, "Help");
}
