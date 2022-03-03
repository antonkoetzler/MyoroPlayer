#pragma once

#include <wx/wx.h>
#include "MenuBar.h"
#include "SongList.h"
#include "Controls.h"

enum
{
  SETDIRINPUT,
  SETDIRBUTTON
};

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  // Menubar functions
  void exit(wxCommandEvent&);
  void showControls(wxCommandEvent&);
  void showSetDirectory(wxCommandEvent&);
  void setDirectory(wxCommandEvent& evt);

  // Playlist events
  void setControls(wxCommandEvent&);

 private:
  DECLARE_EVENT_TABLE();

  MenuBar* menubar;

  // Holds playlist and controls
  wxBoxSizer* sizer;
    SongList* playlist;
    Controls* controls;

  // Popup window used for set directory and yt to mp3 popup windows
  wxFrame* popupWindow;
  wxTextCtrl* input;
  wxButton* button;

  wxString playlistDirectory;
};
