#include "UpdateSlider.h"

UpdateSlider::UpdateSlider(wxSlider* sliderArg, wxMediaCtrl* mediaPlayerArg, SongList* playlistArg) : wxTimer()
{
  mediaPlayer = mediaPlayerArg;
  slider = sliderArg;
  playlist = playlistArg;
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

  if (mediaPlayer->GetState() == wxMEDIASTATE_STOPPED)
  {
    std::cout << "Workingqiowne" << std::endl;
  }
}

