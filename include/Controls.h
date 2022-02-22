// Music controls like pausing, playing, next song, etc
#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include <vector>
#include "SongList.h"
#include "UpdateSlider.h"

enum
{
  MEDIA,
  SHUFFLE,
  PLAYPREVIOUS,
  PLAY,
  PLAYNEXT
};

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*);

  void loadSong(wxString, SongList*);
  void playSong(wxMediaEvent&);

  void togglePlay(wxCommandEvent&);
  void toggleShuffle(wxCommandEvent&);

 private:
  DECLARE_EVENT_TABLE();

  wxBoxSizer* divider; // Divides play/pause, album cover, etc
  wxBoxSizer* playControls; // Sizer for play/pause, next song, song slider
    wxBoxSizer* playControlsButtons; // Sizer for actual play/pause buttons
      wxBitmapButton* shuffle;
        int shuffleToggle = 0;
      wxBitmapButton* playPrevious;
      wxBitmapButton* playButton;
      wxBitmapButton* playNext;
    wxSlider* songSlider;
      UpdateSlider* updateslider;

  wxMediaCtrl* mediaPlayer = nullptr;
  SongList* playlist = nullptr; // Pointer to currently displayed SongList*
  std::vector<wxString> songCache;
};
