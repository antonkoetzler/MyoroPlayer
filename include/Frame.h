#pragma once

#include <wx/wx.h>
#include "MenuBar.h"

class Frame : public wxFrame
{
public:
  Frame();

  // Event functions
  void exit(wxCommandEvent&);
  void showAbout(wxCommandEvent&);

private:
  MenuBar* menubar;

  wxDECLARE_EVENT_TABLE();
};
