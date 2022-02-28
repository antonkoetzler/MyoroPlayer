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
  QUEUE
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

  void addToQueue(wxCommandEvent&);

 private:
  DECLARE_EVENT_TABLE();

  // Menubar
  MenuBar* menubar;

  // Holds the playlist
  SongList* playlist;

  // Holds the music controls, slider, etc
  Controls* controls = nullptr;

  // Sizer to hold music controls and playlist
  wxBoxSizer* sizer;

  // Window/frame for setting song directory
  wxFrame* setDirectoryWindow;
  wxBoxSizer* setDirectorySizer;
  wxTextCtrl* setDirectoryInput;
  wxButton* setDirectoryButton;

  // Apparently the queue vector needs to be placed here
  // Or a weird error occurs if you do Controls::addToQueue
  wxVector<wxString> queue;
};
