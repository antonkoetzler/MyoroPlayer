#include "UpdateSlider.h"

UpdateSlider::UpdateSlider(wxSlider* sliderArg, wxMediaCtrl* mediaPlayerArg) : wxTimer()
{
  mediaPlayer = mediaPlayerArg;
  slider = sliderArg;
  Start(500);
}

void UpdateSlider::Notify()
{
  // Setting slider range
  wxLongLong songLength = mediaPlayer->Length();
  int songLengthSeconds = (int) (songLength / 1000).GetValue();
  slider->SetRange(0, songLengthSeconds);

  // Updating slider's position
  wxLongLong songAt = mediaPlayer->Tell();
  int songAtSeconds = (int) (songAt / 1000).GetValue();
  slider->SetValue(songAtSeconds);
}

