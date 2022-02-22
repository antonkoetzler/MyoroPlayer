#include "UpdateSlider.h"

UpdateSlider::UpdateSlider(wxSlider* sliderArg, wxMediaCtrl* mediaPlayerArg, SongList* playlistArg) : wxTimer()
{
  slider = sliderArg;
  mediaPlayer = mediaPlayerArg;
  playlist = playlistArg;
  Start(0);
}

void UpdateSlider::Notify()
{
  // Setting where the slider should be in the song
  wxLongLong songAt = mediaPlayer->Tell();
  int songAtSeconds = (int)(songAt / 1000).GetValue();
  slider->SetValue(songAtSeconds);
}
