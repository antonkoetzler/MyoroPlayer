#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include <stdlib.h>
#include "SongList.h"

class UpdateSlider : public wxTimer
{
 public:
  UpdateSlider(wxSlider*, wxMediaCtrl*, SongList*, wxVector<wxString>, int, wxString);
  void Notify() wxOVERRIDE;
  void setShuffle(int);
  wxVector<wxString> getSongCache();
  wxString getCurrentSong();
  bool getReturnSongs();

 private:
  wxSlider* slider;
  wxMediaCtrl* mediaPlayer;
  SongList* playlist;
  wxVector<wxString> songCache;
    bool returnSongs = false;
  int shuffleOn = 0;
  wxString currentSong;
};

