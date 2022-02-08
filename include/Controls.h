// Music controls like pausing, playing, next song, etc
#pragma once

#include <wx/wx.h>

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*);

 private:
  wxBoxSizer* divider; // Divides play/pause, album cover, etc
  wxBoxSizer* playControls; // play/pause, next song, song slider
    wxSlider* songSlider;
};
