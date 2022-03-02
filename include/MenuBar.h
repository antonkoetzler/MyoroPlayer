#pragma once

#include <wx/wx.h>

enum
{
  SETDIR,
  SHOWCONTROLS,
  ABOUT,
  YT2MP3,
  REFRESH
};

class MenuBar : public wxMenuBar
{
public:
  MenuBar();

private:
  wxMenu* file;
    wxMenuItem* fileSetDirectory;
    wxMenuItem* fileYt2Mp3;
    wxMenuItem* fileExit;
  wxMenu* view;
    wxMenuItem* viewRefresh;
    wxMenuItem* viewShowControls;
  wxMenu* help;
    wxMenuItem* helpAbout;
};
