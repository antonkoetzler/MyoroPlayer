#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include <stdlib.h>
#include "SongList.h"
#include "UpdateSlider.h"

enum
{
  MEDIA,
  SLIDER,
  VOLUME,
  SHUFFLE,
  PREVIOUS,
  PLAY,
  NEXT
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

  // wxSlider event
  void changeSliderPosition(wxScrollEvent&);

  // Setters
  void setPlaylist(SongList*);
  void addToSongCache(wxString);
  void setPlaylistDirectory(wxString);

  // musicControl button functions
  void previousSong(wxCommandEvent&);
  void toggleShuffle(wxCommandEvent&);
  void togglePause(wxCommandEvent&);
  void nextSong(wxCommandEvent&);

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
          int shuffleToggle = 0;
        wxButton* previous;
        wxButton* play;
        wxButton* next;

    wxSlider* volume;

  wxMediaCtrl* mediaPlayer = nullptr;
  SongList* playlist;
  UpdateSlider* updateslider = nullptr;
  wxVector<wxString> songCache;

  #ifdef linux
    wxString playlistDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs/";
  #endif
  #ifdef _WIN32
    wxString playlistDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs\\";
  #endif
};
