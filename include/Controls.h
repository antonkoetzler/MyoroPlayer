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
  MEDIA,
  VOLUME
};

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*, wxSize&);

  void setMediaPlayer(wxString, SongList*);
  void playSong(wxMediaEvent&);
  void changeCurrentTimePlaying(wxScrollEvent& evt);

  void previousSong(wxCommandEvent&);
  void togglePause(wxCommandEvent&);
  void nextSong(wxCommandEvent&);
  void toggleShuffle(wxCommandEvent&);

  void setQueue(wxVector<wxString>);

 private:
  DECLARE_EVENT_TABLE();

  wxBoxSizer* divider;
    // What is playing, title, extension
    wxPanel* songDetailsContainer;
      wxBoxSizer* songDetailsSizer;
        wxStaticBitmap* musicNote;
        wxStaticText* details;
    // Play/pause, next, previous, shuffle, and music slider/gauge
    wxBoxSizer* mainControls;
      wxSlider* slider;
      wxBoxSizer* mainControlsButtons;
        wxButton* shuffle;
          int shuffleToggle = 0;
        wxButton* previous;
        wxButton* play;
        wxButton* next;
    // Volume Control
    wxSlider* volume;

  wxMediaCtrl* mediaPlayer = nullptr;
  UpdateSlider* updateslider = nullptr;
  SongList* playlist;
  wxVector<wxString> songCache;
  wxVector<wxString> queue;
};
