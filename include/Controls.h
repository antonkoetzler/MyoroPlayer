#pragma once

#include <wx/wx.h>

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*);

  // Setup functions
  void setMusicControls();

 private:
  // Holds: song info, music controls, volume
  wxBoxSizer* divider;
    // Holds: Music guage/slider, buttons (play/pause, next, previous, and shuffle)
    wxBoxSizer* musicControls;
      wxSlider* slider;
      wxBoxSizer* buttons;
        wxButton* shuffle;
        wxButton* previous;
        wxButton* play;
        wxButton* next;
};
