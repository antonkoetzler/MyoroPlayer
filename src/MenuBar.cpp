#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  setDirectory = new wxMenuItem(
    nullptr,
    SETDIR,
    "Set Directory\tCtrl+W"
  );

  setYt2Mp3 = new wxMenuItem(
    nullptr,
    YT2MP3,
    "Convert YouTube Link To MP3\tCtrl+E"
  );

  fileExit = new wxMenuItem(
    nullptr,
    wxID_EXIT,
    "Exit MyoroPlayer\tCtrl+Q"
  );

  file = new wxMenu();
  file->Append(setDirectory);
  file->Append(setYt2Mp3);
  file->Append(fileExit);

  refreshDirectory = new wxMenuItem(
    nullptr,
    REFRESH,
    "Refresh Directory\tCtrl+R"
  );

  viewShowControls = new wxMenuItem(
    nullptr,
    SHOWCONTROLS,
    "Show controls"
  );

  view = new wxMenu();
  view->Append(refreshDirectory);
  view->Append(viewShowControls);

  Append(file, "File");
  Append(view, "View");
}
