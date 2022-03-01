#pragma once

#include <wx/wx.h>
#include <wx/uiaction.h>
#include "MenuBar.h"
#include "SongList.h"
#include "Controls.h"

enum
{
  SETDIRINPUT,
  SETDIRBUTTON,
  QUEUE,
  YT2MP3BUTTON,
  YT2MP3INPUT
};

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  void exit(wxCommandEvent&);
  void setControls(wxCommandEvent&);
  void showSetDirectory(wxCommandEvent&);
  void setDirectory(wxCommandEvent&);
  void showControls(wxCommandEvent&);
  void songMenu(wxMouseEvent&);
  void showYt2Mp3(wxCommandEvent&);
  void Yt2Mp3(wxCommandEvent&);
  void addToQueue(wxCommandEvent&);

 private:
  DECLARE_EVENT_TABLE();

  // Menubar
  MenuBar* menubar;

  // Holds the playlist
  SongList* playlist;
  #ifdef linux
    wxString playlistDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs/";
  #endif
  #ifdef _WIN32
    wxString playlistDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs\\";
  #endif

  // Holds the music controls, slider, etc
  Controls* controls = nullptr;

  // Sizer to hold music controls and playlist
  wxBoxSizer* sizer;

  // Window/frame for setting song directory and youtube2mp3 conversion
  wxFrame* setterWindow;
  wxBoxSizer* setterWindowSizer;
  wxTextCtrl* setterWindowInput;
  wxButton* setterWindowButton;

  // Apparently the queue vector needs to be placed here
  // Or a weird error occurs if you do Controls::addToQueue
  wxVector<wxString> queue;
};
