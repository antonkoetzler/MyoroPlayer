#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include <stdlib.h>
#include "SongList.h"

class UpdateSlider : public wxTimer
{
 public:
  UpdateSlider(wxSlider*, wxMediaCtrl*, SongList*, int, wxVector<wxString>, wxVector<wxString>, wxString);

  void Notify() wxOVERRIDE;

  // Setter
  void addToQueue(wxString);
  void setQueue(wxVector<wxString>);

 private:
  wxSlider* slider;
  wxMediaCtrl* mediaPlayer;
  SongList* playlist;
  int shuffleToggle;
  wxVector<wxString> songCache;
  wxVector<wxString> queue;
  wxString playlistDirectory;
};
