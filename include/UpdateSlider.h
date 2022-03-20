#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include "SongList.h"

class UpdateSlider : public wxTimer
{
 public:
  UpdateSlider(wxSlider*, wxMediaCtrl*, SongList*);
  void Notify() wxOVERRIDE;

 private:
  wxSlider* slider;
  wxMediaCtrl* mediaPlayer;
  SongList* playlist;
};

