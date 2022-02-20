#pragma once

#include <wx/wx.h>
#include "SongList.h"
#include "MenuBar.h"
#include "Controls.h"

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  // Acquires songlist & song name (wxListBox item clicked)
  // Transfers this information to Controls::playSong(...)
  void getSongAndPlaylist(wxCommandEvent& evt);

 private:
  DECLARE_EVENT_TABLE();

  wxBoxSizer* ui; // Sizer for dividing song list, music controls, etc
  SongList* songlist;
  MenuBar* menubar;
  Controls* controls;
};

