#pragma once

#include <wx/wx.h>

enum
{
  SHOWCONTROLS,
  CHANGE_DIR
};

class MenuBar : public wxMenuBar
{
 public:
  MenuBar();

 private:
  wxMenu* file;
    wxMenuItem* fileExit;
    wxMenuItem* fileChangeDirectory;
  wxMenu* view;
    wxMenuItem* viewShowControls;
};

