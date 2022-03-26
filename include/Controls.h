#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include <stdlib.h>       // rand()
#include "SongList.h"
#include "UpdateSlider.h"

enum
{
  MEDIA,
  SHUFFLE,
  PREV,
  PLAY,
  NEXT
};

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*);

  void setMainControls();         // Sets up mainControls

  void initMediaPlayer(wxString);
  void playSong(wxMediaEvent&);

  void setPlaylist(SongList*);

  // Button (shuffle, prev, play/pause, next) event functions
  void toggleShuffle(wxCommandEvent&);
  void previousSong(wxCommandEvent&);
  void togglePlay(wxCommandEvent&);
  void nextSong(wxCommandEvent&);

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
          int shuffleOn = 0;
        wxButton* previous;
        wxButton* play;
        wxButton* next;

    wxSlider* volume;

  wxMediaCtrl* mediaPlayer = nullptr;
  SongList* playlist = nullptr;
  UpdateSlider* updateSlider = nullptr;

  wxVector<wxString> songCache;
  wxString currentSong = wxEmptyString;
};

