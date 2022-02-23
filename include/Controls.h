// Music slider/guage, play/pause, next/previous, etc
#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include "SongList.h"
#include "UpdateSlider.h"

enum
{
  SLIDER,
  PREVIOUS,
  PLAY,
  NEXT,
  SHUFFLE,
  MEDIA
};

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*, wxSize&);

  void setMediaPlayer(wxString, SongList*);
  void playSong(wxMediaEvent&);
  void changeCurrentTimePlaying(wxScrollEvent& evt);

  //void previousSong(wxCommandEvent&);
  void togglePause(wxCommandEvent&);
  //void nextSong(wxCommandEvent&);
  void toggleShuffle(wxCommandEvent&);

 private:
  DECLARE_EVENT_TABLE();

  wxBoxSizer* divider;
    // Play/pause, next, previous, shuffle, and music slider/gauge
    wxBoxSizer* mainControls;
      wxSlider* slider;
      wxBoxSizer* mainControlsButtons;
        wxButton* shuffle;
          int shuffleToggle = 0;
        wxButton* previous;
        wxButton* play;
        wxButton* next;

  wxMediaCtrl* mediaPlayer = nullptr;
  UpdateSlider* updateslider = nullptr;
  SongList* playlist;
};
