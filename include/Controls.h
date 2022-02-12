// Music controls like pausing, playing, next song, etc
#pragma once

#include <wx/wx.h>

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*);

 private:
  wxBoxSizer* divider; // Divides play/pause, album cover, etc
  wxBoxSizer* playControls; // Sizer for play/pause, next song, song slider
    wxBoxSizer* playControlsButtons; // Sizer for actual play/pause buttons
      wxBitmapButton* shuffle;
      wxBitmapButton* playPrevious;
      wxBitmapButton* playButton;
      wxBitmapButton* playNext;
    wxSlider* songSlider;
};
