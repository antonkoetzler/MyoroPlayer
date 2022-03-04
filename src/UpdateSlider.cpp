#include "UpdateSlider.h"

UpdateSlider::UpdateSlider(wxSlider* sliderArg, wxMediaCtrl* mediaPlayerArg, SongList* playlistArg, int shuffleToggleArg, wxVector<wxString> songCacheArg, wxVector<wxString> queueArg, wxString playlistDirectoryArg) : wxTimer()
{
  slider = sliderArg;
  mediaPlayer = mediaPlayerArg;
  playlist = playlistArg;
  shuffleToggle = shuffleToggleArg;
  songCache = songCacheArg;
  queue = queueArg;
  playlistDirectory = playlistDirectoryArg;
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

  if (mediaPlayer->GetState() == wxMEDIASTATE_STOPPED)
  {
    int nextSongIndex = 0;

    if (!queue.empty())
    {
      wxString song = queue[queue.size() - 1];
      queue.pop_back();

      for (int i = (song.length() - 1); i >= 0; i--)
      {
        #ifdef linux
          if (song[i] == '/')
          {
            song = song.substr(i + 1);
            break;
          }
        #endif
        #ifdef _WIN32
          if (song[i] == '\\')
          {
            song = song.substr(i + 1);
            break;
          }
        #endif
      }

      nextSongIndex = playlist->FindString(song);
    }
    else if (shuffleToggle == 0)
    {
      wxString song = songCache[songCache.size() - 1];
      for (int i = (song.length() - 1); i >= 0; i--)
      {
        #ifdef linux
          if (song[i] == '/')
          {
            song = song.substr(i + 1);
            break;
          }
        #endif
        #ifdef _WIN32
          if (song[i] == '\\')
          {
            song = song.substr(i + 1);
            break;
          }
        #endif
      }

      nextSongIndex = playlist->FindString(song);
      if (nextSongIndex == (playlist->GetCount() - 1))
        nextSongIndex = 0;
      else
        nextSongIndex += 1;
    }
    else
      nextSongIndex = rand() & playlist->GetCount();

    playlist->SetSelection(nextSongIndex);

    wxString songDirectory = playlist->GetString(nextSongIndex);
    songDirectory = playlistDirectory + songDirectory;

    if (!mediaPlayer->Load(songDirectory))
    {
      std::cout << "!mediaPlayer->Load(songDirectory)" << std::endl;
      exit(1);
    }
  }
}

void UpdateSlider::addToQueue(wxString song) { queue.push_back(song); }

void UpdateSlider::setQueue(wxVector<wxString> queueArg)
{
  queue.clear();
  queue = queueArg;
}
