#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include "SongList.h"

enum
{
  MEDIA
};

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*);

  // Setup functions
  void setMusicControls();
  void setSongInformation();
  void setMediaPlayer(wxString);

  // mediaPlayer functions
  void playSong(wxMediaEvent&);

  // Setters
  void setPlaylist(SongList*);

 private:
  DECLARE_EVENT_TABLE();

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

  wxMediaCtrl* mediaPlayer = nullptr;
  SongList* playlist;
};
