#pragma once

#include <wx/wx.h>

enum
{
  SETDIR,
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
  wxMenu* help;
    wxMenuItem* helpAbout;
};
