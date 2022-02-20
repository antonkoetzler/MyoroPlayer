// Music controls like pausing, playing, next song, etc
#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include <vector>
#include "SongList.h"

enum { MEDIA };

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*);

  void loadSong(wxString, SongList*);
  void playSong(wxMediaEvent&);

 private:
  DECLARE_EVENT_TABLE();

  wxBoxSizer* divider; // Divides play/pause, album cover, etc
  wxBoxSizer* playControls; // Sizer for play/pause, next song, song slider
    wxBoxSizer* playControlsButtons; // Sizer for actual play/pause buttons
      wxBitmapButton* shuffle;
      wxBitmapButton* playPrevious;
      wxBitmapButton* playButton;
      wxBitmapButton* playNext;
    wxSlider* songSlider;

  wxMediaCtrl* mediaPlayer = nullptr;
  SongList* playlist = nullptr; // Pointer to currently displayed SongList*
  std::vector<wxString> songCache;
};
