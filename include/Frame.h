#pragma once

#include <wx/wx.h>
#include "MenuBar.h"
#include "Interface.h"
#include "About.h"

class Frame : public wxFrame
{
public:
  Frame();
  ~Frame();

  void showAbout(wxCommandEvent&);
  void exit(wxCommandEvent&);

private:
  MenuBar* menubar;
  Interface* interface;
  About* aboutWindow;
  wxDECLARE_EVENT_TABLE();
};
