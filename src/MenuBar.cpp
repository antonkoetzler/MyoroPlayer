#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileExit = new wxMenuItem(nullptr, wxID_EXIT, "Exit\tCtrl+Q");
  fileYt2Mp3 = new wxMenuItem(nullptr, YT2MP3, "Convert YouTube to MP3\tCtrl+E");
  fileChangeDirectory = new wxMenuItem(nullptr, CHANGE_DIR, "Change Directory\tCtrl+W");

  file = new wxMenu();
  file->Append(fileYt2Mp3);
  file->Append(fileChangeDirectory);
  file->Append(fileExit);

  viewRefreshPlaylist = new wxMenuItem(nullptr, REFRESH, "Refresh Playlist\tCtrl+R");
  viewShowControls = new wxMenuItem(nullptr, SHOWCONTROLS, "Show Controls");

  view = new wxMenu();
  view->Append(viewRefreshPlaylist);
  view->Append(viewShowControls);

  Append(file, "File");
  Append(view, "View");
}

