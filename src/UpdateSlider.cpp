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

  // End of song condition
  if (slider->GetValue() == slider->GetMax())
  {
    int nextSongIndex = 0;
    // Checking if we're on shuffle or not
    switch (shuffleToggle)
    {
      case 0:
        nextSongIndex = playlist->GetSelection() + 1;
        if (nextSongIndex > (playlist->GetCount() - 1))
          nextSongIndex = 0;
        break;
      case 1:
        nextSongIndex = rand() % playlist->GetCount();
        break;
    }

    // Loading the song
    wxString songName = playlist->GetString(nextSongIndex);
    #ifdef linux
      wxString songDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs/" + songName;
    #endif
    #ifdef _WIN32
      wxString songDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs\\" + songName;
    #endif

    if (!mediaPlayer->Load(songDirectory))
    {
      std::cout << "!mediaPlayer->Load(songDirectory)" << std::endl;
      exit(1);
    }

    playlist->SetSelection(nextSongIndex);
  }
}

void UpdateSlider::setShuffleToggle(int shuffleToggleArg)
{
  shuffleToggle = shuffleToggleArg;
}
