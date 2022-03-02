#pragma once

#include <wx/wx.h>
#include "MenuBar.h"
#include "SongList.h"
#include "Controls.h"

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  // Menubar functions
  void exit(wxCommandEvent&);
  void showControls(wxCommandEvent&);

  // Playlist events
  void setControls(wxCommandEvent&);

 private:
  DECLARE_EVENT_TABLE();

  MenuBar* menubar;

  // Holds playlist and controls
  wxBoxSizer* sizer;
    SongList* playlist;
    Controls* controls;
};
