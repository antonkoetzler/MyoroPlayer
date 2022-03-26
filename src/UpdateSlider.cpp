#include "UpdateSlider.h"

UpdateSlider::UpdateSlider(wxSlider* sliderArg, wxMediaCtrl* mediaPlayerArg, SongList* playlistArg, wxVector<wxString> songCacheArg, int shuffleArg, wxString currentSongArg) : wxTimer()
{
  mediaPlayer = mediaPlayerArg;
  slider = sliderArg;
  playlist = playlistArg;
  songCache = songCacheArg;
  shuffleOn = shuffleArg;
  currentSong = currentSongArg;
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
    songCache.push_back(currentSong);

    int nextSongIndex = 0;

    wxString currentSongParsed = wxEmptyString;
    if (shuffleOn == 0)
    {
      // Removing directory from currentSong
      for (int i = (currentSong.length() - 1); i >= 0; i--)
      {
        #ifdef linux
        if (currentSong[i] == '/')
        #endif
        #ifdef _WIN32
        if (currentSong[i] == '\\')
        #endif
        {
          currentSongParsed = currentSong.substr(i + 1);
          break;
        }
      }

      nextSongIndex = playlist->FindString(currentSongParsed);
      if (nextSongIndex == (playlist->GetCount() - 1))
        nextSongIndex = 0;
      else
        nextSongIndex += 1;
    } else nextSongIndex = rand() % playlist->GetCount();

    playlist->SetSelection(nextSongIndex);

    // Getting the next song's filename + directory
    currentSong = playlist->GetString(nextSongIndex);
    currentSong = playlist->getPlaylistDirectory() + currentSong;

    returnSongs = true;

    if (!mediaPlayer->Load(currentSong)) { exit(1); }
  }
}

void UpdateSlider::setShuffle(int shuffleArg) { shuffleOn = shuffleArg; }

wxVector<wxString> UpdateSlider::getSongCache() { return songCache; }

wxString UpdateSlider::getCurrentSong() { return currentSong; } 

bool UpdateSlider::getReturnSongs() { return returnSongs; }

