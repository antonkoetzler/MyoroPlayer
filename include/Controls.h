#pragma once

#include <wx/wx.h>

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*);

  // Setup functions
  void setMusicControls();
  void setSongInformation();

 private:
  // Holds: song info, music controls, volume
  wxBoxSizer* divider;
    // Holds: Album cover (not rn), song name, and song extension
    wxBoxSizer* songInformation;
      wxStaticBitmap* songCover;
      wxStaticText* fileDetails;

    // Holds: Music guage/slider, buttons (play/pause, next, previous, and shuffle)
    wxBoxSizer* musicControls;
      wxSlider* slider;
      wxBoxSizer* buttons;
        wxButton* shuffle;
        wxButton* previous;
        wxButton* play;
        wxButton* next;

    wxSlider* volume;
};
