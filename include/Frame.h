#pragma once

#include <wx/wx.h>
#include "MenuBar.h"
#include "SongList.h"
#include "Controls.h"

enum
{
  SETDIRINPUT,
  SETDIRBUTTON,
  QUEUE,
  YT2MP3INPUT,
  YT2MP3BUTTON
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
  void showYt2Mp3(wxCommandEvent&);
  void Yt2Mp3(wxCommandEvent&);
  void refreshPlaylist(wxCommandEvent&);

  // Popup menu
  void playlistMenu(wxMouseEvent&);
  void queueSong(wxCommandEvent&);

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

  #ifdef linux
    wxString playlistDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs/";
  #endif
  #ifdef _WIN32
    wxString playlistDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs\\";
  #endif
};
