#include "UpdateSlider.h"

UpdateSlider::UpdateSlider(wxSlider* sliderArg, wxMediaCtrl* mediaPlayerArg, SongList* playlistArg) : wxTimer()
{
  slider = sliderArg;
  mediaPlayer = mediaPlayerArg;
  playlist = playlistArg;
  playlistDirectory = playlist->getDirectory();
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
  if (mediaPlayer->GetState() == wxMEDIASTATE_STOPPED)
  {
    int nextSongIndex = 0;
    wxString songName;
    wxString songDirectory;

    if (queue.empty())
    {
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

      songName = playlist->GetString(nextSongIndex);
      playlist->SetSelection(nextSongIndex);

      songDirectory = playlistDirectory + songName;
    }
    else
    {
      songDirectory = queue[queue.size() - 1];
      queue.pop_back();

      // Setting the selection
      for (int i = (songDirectory.length() - 1); i >= 0; i--)
      {
        #ifdef linux
          if (songDirectory[i] == '/')
          {
            songName = songDirectory.substr(i + 1);
            break;
          }
        #endif
        #ifdef _WIN32
          if (songDirectory[i] == '\\')
          {
            songName = songDirectory.substr(i + 1);
            break;
          }
        #endif
      }
      playlist->SetSelection(playlist->FindString(songName));
    }

    tempSongDirectory = songDirectory;

    if (!mediaPlayer->Load(songDirectory))
    {
      std::cout << "!mediaPlayer->Load(songDirectory)" << std::endl;
      exit(1);
    }

    tempSongDirectory = wxEmptyString;
  }
}

void UpdateSlider::setShuffleToggle(int shuffleToggleArg) { shuffleToggle = shuffleToggleArg; }

void UpdateSlider::setQueue(wxVector<wxString> queueArg) { queue = queueArg; }

wxString UpdateSlider::getTempSongDirectory() { return tempSongDirectory; }

