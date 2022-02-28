#pragma once

#include <wx/wx.h>

enum
{
  SETDIR,
  SHOWCONTROLS,
  ABOUT,
  YT2MP3
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
    wxMenuItem* viewShowControls;
  wxMenu* help;
    wxMenuItem* helpAbout;
};
