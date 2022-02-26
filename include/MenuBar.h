#pragma once

#include <wx/wx.h>

enum
{
  SETDIR,
  SHOWCONTROLS,
  ABOUT
};

class MenuBar : public wxMenuBar
{
public:
  MenuBar();

private:
  wxMenu* file;
    wxMenuItem* fileSetDirectory;
    wxMenuItem* fileExit;
  wxMenu* view;
    wxMenuItem* viewShowControls;
  wxMenu* help;
    wxMenuItem* helpAbout;
};
