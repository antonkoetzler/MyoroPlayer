#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include "SongList.h"

enum { MEDIA };

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*);

  void setMainControls();         // Sets up mainControls

  void initMediaPlayer(wxString);

  void playSong(wxMediaEvent&);

  void setPlaylist(SongList*);

 private:
  DECLARE_EVENT_TABLE();

  // Sizer for each section of the music controls
  wxBoxSizer* sizer;
    wxStaticText* songInformation;

    // Sizer for buttons (play/pause, next, prev, shuffle) & music slider
    wxBoxSizer* mainControls;
      wxSlider* slider;
      wxBoxSizer* mainControlsButtons;
        wxButton* shuffle;
        wxButton* previous;
        wxButton* play;
        wxButton* next;

    wxSlider* volume;

  wxMediaCtrl* mediaPlayer = nullptr;
  SongList* playlist = nullptr;
};

