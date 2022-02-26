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

  viewShowControls = new wxMenuItem(
    nullptr,
    SHOWCONTROLS,
    "Show controls"
  );

  view = new wxMenu();
  view->Append(viewShowControls);

  helpAbout = new wxMenuItem(
    nullptr,
    ABOUT,
    "About MyoroPlayer"
  );

  help = new wxMenu();
  help->Append(helpAbout);

  Append(file, "File");
  Append(view, "View");
  Append(help, "Help");
}
