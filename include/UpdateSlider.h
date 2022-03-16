#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>

class UpdateSlider : public wxTimer
{
 public:
  UpdateSlider(wxSlider*, wxMediaCtrl*);
  void Notify() wxOVERRIDE;

 private:
  wxSlider* slider;
  wxMediaCtrl* mediaPlayer;
};

