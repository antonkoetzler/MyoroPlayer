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

  viewShowControls = new wxMenuItem(
    nullptr,
    SHOWCONTROLS,
    "Show controls"
  );

  view = new wxMenu();
  view->Append(viewShowControls);

  Append(file, "File");
  Append(view, "View");
}
