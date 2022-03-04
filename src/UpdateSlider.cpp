#include "UpdateSlider.h"

UpdateSlider::UpdateSlider(wxSlider* sliderArg, wxMediaCtrl* mediaPlayerArg, SongList* playlistArg) : wxTimer()
{
  slider = sliderArg;
  mediaPlayer = mediaPlayerArg;
  playlist = playlistArg;
  Start(500);
}

void UpdateSlider::Notify()
{
  // Setting slider range
  wxLongLong songLength = mediaPlayer->Length();
  int songLengthSeconds = (int) (songLength / 1000).GetValue();
  slider->SetRange(0, songLengthSeconds);

  // Setting where the slider should be in the song
  wxLongLong songAt = mediaPlayer->Tell();
  int songAtSeconds = (int)(songAt / 1000).GetValue();
  slider->SetValue(songAtSeconds);
}
