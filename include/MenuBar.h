#pragma once

#include <wx/wx.h>

class MenuBar : public wxMenuBar
{
 public:
  MenuBar();

 private:
  wxMenu* file;
    wxMenuItem* fileQuit;
};
