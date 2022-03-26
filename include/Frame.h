#pragma once

#include <wx/wx.h>
#include "MenuBar.h"
#include "SongList.h"
#include "Controls.h"

enum
{
  YT2MP3_INP,
  YT2MP3_BUTTON,
  CHANGE_DIR_INP,
  CHANGE_DIR_BUTTON,
  QUEUE
};

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  // MenuBar event functions
  void yt2Mp3(wxCommandEvent&);
    void convertLink(wxCommandEvent&);
  void changeDirectory(wxCommandEvent&);
    void setDirectory(wxCommandEvent&);
  void exit(wxCommandEvent&);
  void refreshPlaylist(wxCommandEvent&);
  void toggleControls(wxCommandEvent&);
  void playlistMenu(wxMouseEvent&);
    void queueSong(wxCommandEvent&);

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

  // For popup windows
  wxFrame* popup = nullptr;
  wxTextCtrl* inp = nullptr;
};

