#pragma once

#include <wx/wx.h>

enum
{
  YT2MP3,
  CHANGE_DIR,
  REFRESH,
  SHOWCONTROLS
};

class MenuBar : public wxMenuBar
{
 public:
  MenuBar();

 private:
  wxMenu* file;
    wxMenuItem* fileExit;
    wxMenuItem* fileYt2Mp3;
    wxMenuItem* fileChangeDirectory;
  wxMenu* view;
    wxMenuItem* viewRefreshPlaylist;
    wxMenuItem* viewShowControls;
};

