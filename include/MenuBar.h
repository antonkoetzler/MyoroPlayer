#pragma once

#include <wx/wx.h>

class MenuBar : public wxMenuBar
{
public:
  MenuBar();

private:
  wxMenu* fileMenu;
    wxMenuItem* fileExit;
  wxMenu* helpMenu;
    wxMenuItem* helpAbout;
};
