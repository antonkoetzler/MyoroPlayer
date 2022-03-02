#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileSetDirectory = new wxMenuItem(
    nullptr,
    SETDIR,
    "Set Directory\tCtrl+W"
  );

  fileYt2Mp3 = new wxMenuItem(
    nullptr,
    YT2MP3,
    "Youtube to MP3 Conversion\tCtrl+Shift+W"
  );

  fileExit = new wxMenuItem(
    nullptr,
    wxID_EXIT,
    "Exit MyoroPlayer\tCtrl+Q"
  );

  file = new wxMenu();
  file->Append(fileSetDirectory);
  file->Append(fileYt2Mp3);
  file->Append(fileExit);

  viewRefresh = new wxMenuItem(
    nullptr,
    REFRESH,
    "Refresh playlist directory\tF5"
  );

  viewShowControls = new wxMenuItem(
    nullptr,
    SHOWCONTROLS,
    "Show controls"
  );

  view = new wxMenu();
  view->Append(viewRefresh);
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
