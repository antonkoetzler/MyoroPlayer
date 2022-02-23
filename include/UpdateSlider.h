// Updates slider member variable in
// Controls.h to sync with the song
#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include <stdlib.h> // rand()
#include "SongList.h"

class UpdateSlider : public wxTimer
{
 public:
  UpdateSlider(wxSlider*, wxMediaCtrl*, SongList*);

  void Notify() wxOVERRIDE;
  void setShuffleToggle(int);

 private:
  wxSlider* slider;
  wxMediaCtrl* mediaPlayer;
  SongList* playlist;
  int shuffleToggle = 0;
};
