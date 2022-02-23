#pragma once

#include <wx/wx.h>

enum
{
  ABOUT
};

class MenuBar : public wxMenuBar
{
public:
  MenuBar();

private:
  wxMenu* file;
    wxMenuItem* fileExit;
  wxMenu* help;
    wxMenuItem* helpAbout;
};
