#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include <stdlib.h>
#include "SongList.h"

class UpdateSlider : public wxTimer
{
 public:
  UpdateSlider(wxSlider*, wxMediaCtrl*, SongList*, wxVector<wxString>, int);
  void Notify() wxOVERRIDE;
  void setShuffle(int);
  wxVector<wxString> getSongCache();

 private:
  wxSlider* slider;
  wxMediaCtrl* mediaPlayer;
  SongList* playlist;
  wxVector<wxString> songCache;
  int shuffleOn = 0;
};

