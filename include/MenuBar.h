#pragma once

#include <wx/wx.h>

enum { SHOWCONTROLS };

class MenuBar : public wxMenuBar
{
 public:
  MenuBar();

 private:
  wxMenu* file;
    wxMenuItem* fileExit;
  wxMenu* view;
    wxMenuItem* viewShowControls;
};

