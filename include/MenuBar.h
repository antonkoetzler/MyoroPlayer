#pragma once

#include <wx/wx.h>

enum
{
  SHOWCONTROLS,
  SETDIR
};

class MenuBar : public wxMenuBar
{
 public:
  MenuBar();

 private:
  wxMenu* file;
    wxMenuItem* setDirectory;
    wxMenuItem* fileExit;
  wxMenu* view;
    wxMenuItem* viewShowControls;
};
