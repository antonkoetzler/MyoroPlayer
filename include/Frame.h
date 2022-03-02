#pragma once

#include <wx/wx.h>
#include "MenuBar.h"
#include "SongList.h"

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  // Menubar functions
  void exit(wxCommandEvent&);

 private:
  DECLARE_EVENT_TABLE();

  MenuBar* menubar;

  // Holds playlist and controls
  wxBoxSizer* sizer;
    SongList* playlist;
};
