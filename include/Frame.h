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

  // MenuBar event functions
  void exit(wxCommandEvent&);
  void toggleControls(wxCommandEvent&);

  // Listbox event functions
  void initSong(wxCommandEvent&);

 private:
  DECLARE_EVENT_TABLE();

  // MenuBar
  MenuBar* menubar;

  // Sizer to hold SongList* and Controls*
  wxBoxSizer* sizer;
  SongList* playlist;
  Controls* controls;
};

