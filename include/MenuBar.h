#pragma once

#include <wx/wx.h>

enum
{
  SHOWCONTROLS,
  SETDIR,
  YT2MP3,
  REFRESH
};

class MenuBar : public wxMenuBar
{
 public:
  MenuBar();

 private:
  wxMenu* file;
    wxMenuItem* setDirectory;
    wxMenuItem* setYt2Mp3;
    wxMenuItem* fileExit;
  wxMenu* view;
    wxMenuItem* refreshDirectory;
    wxMenuItem* viewShowControls;
};
