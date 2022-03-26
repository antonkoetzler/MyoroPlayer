#include "Controls.h"

BEGIN_EVENT_TABLE(Controls, wxPanel)
  // Catching mediaPlayer->Load(...)
  EVT_MEDIA_LOADED(MEDIA, Controls::playSong)

  // Button (shuffle, prev, play/pause, next)  events
  EVT_BUTTON(SHUFFLE, Controls::toggleShuffle)
  EVT_BUTTON(PREV, Controls::previousSong)
  EVT_BUTTON(PLAY, Controls::togglePlay)
  EVT_BUTTON(NEXT, Controls::nextSong)
END_EVENT_TABLE()

Controls::Controls(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1000, 90))
{
  #ifdef linux
    songInformation = new wxStaticText(
      this,
      wxID_ANY,
      "\nSong Name\nSong Extension",
      wxDefaultPosition,
      wxSize(190, 75),
      wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE | wxST_ELLIPSIZE_END
    );
  #endif
  #ifdef _WIN32
    songInformation = new wxStaticText(
      this,
      wxID_ANY,
      "\nSong Name\nSongExtension",
      wxDefaultPosition,
      wxSize(190, 90),
      wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE | wxST_ELLIPSIZE_END
    );
  #endif
  songInformation->SetFont(wxFont(
    14,
    wxFONTFAMILY_DEFAULT,
    wxFONTSTYLE_NORMAL,
    wxFONTWEIGHT_NORMAL
  ));

  setMainControls();

  volume = new wxSlider(
    this,
    wxID_ANY,
    100,
    0,
    100,
    wxDefaultPosition,
    wxSize(200, 35)
  );

  sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->Add(songInformation, 0, wxLEFT | wxALIGN_CENTRE, 10);
  sizer->AddStretchSpacer();
  sizer->Add(mainControls, 0);
  sizer->AddStretchSpacer();
  sizer->Add(volume, 0, wxALIGN_CENTRE);
  SetSizer(sizer);
}

void Controls::setMainControls()
{
  #ifdef linux
    slider = new wxSlider(
      this,
      wxID_ANY,
      1,
      0,
      100,
      wxDefaultPosition,
      wxSize(200, 40)
    );
  #endif
  #ifdef _WIN32
    slider = new wxSlider(
      this,
      wxID_ANY,
      1,
      0,
      100,
      wxDefaultPosition,
      wxSize(200, 30)
    );
  #endif

  shuffle = new wxButton(
    this,
    SHUFFLE,
    "%",
    wxDefaultPosition,
    wxSize(40, 40),
    wxBORDER_NONE
  );
  previous = new wxButton(
    this,
    PREV,
    "<<",
    wxDefaultPosition,
    wxSize(40, 40),
    wxBORDER_NONE
  );
  play = new wxButton(
    this,
    PLAY,
    ">",
    wxDefaultPosition,
    wxSize(40, 40),
    wxBORDER_NONE
  );
  next = new wxButton(
    this,
    NEXT,
    ">>",
    wxDefaultPosition,
    wxSize(40, 40),
    wxBORDER_NONE
  );

  // Where buttons are placed
  mainControlsButtons = new wxBoxSizer(wxHORIZONTAL);
  mainControlsButtons->Add(shuffle, 0, wxRIGHT, 10);
  mainControlsButtons->Add(previous, 0, wxRIGHT, 10);
  mainControlsButtons->Add(play, 0, wxRIGHT, 10);
  mainControlsButtons->Add(next, 0);

  // Where slider and mainControlsButtons are placed
  mainControls = new wxBoxSizer(wxVERTICAL);
  mainControls->Add(slider, 0, wxALL | wxALIGN_CENTRE, 5);
  mainControls->Add(mainControlsButtons, 0, wxALIGN_CENTRE);
}

void Controls::initMediaPlayer(wxString songDirectory)
{
  if (mediaPlayer != nullptr) { delete mediaPlayer; mediaPlayer = nullptr; }

  #ifdef linux
    mediaPlayer = new wxMediaCtrl(this, MEDIA);
  #endif
  #ifdef _WIN32
    mediaPlayer = new wxMediaCtrl(
      this,
      MEDIA,
      wxEmptyString,
      wxDefaultPosition,
      wxDefaultSize,
      0,
      wxMEDIABACKEND_WMP10
    );
  #endif

  mediaPlayer->SetVolume(1.0);

  // Putting the song that was playing into songCache
  if (currentSong != wxEmptyString) songCache.push_back(currentSong);
  currentSong = songDirectory;

  if (!mediaPlayer->Load(currentSong)) { exit(1); }
}

void Controls::playSong(wxMediaEvent& evt)
{
  if (updateSlider != nullptr)
  {
    if (updateSlider->getReturnSongs())
    {
      currentSong = updateSlider->getCurrentSong();
      songCache = updateSlider->getSongCache();
    }
    delete updateSlider; updateSlider = nullptr;
  }

  // Getting song name and extension to display
  wxString song = playlist->GetString(playlist->GetSelection());
  wxString songExtension;

  for (int i = (song.length() - 1); i >= 0; i--)
  {
    if (song[i] == '.')
    {
      songExtension = song.substr(i + 1);
      songExtension.MakeUpper();
      song = song.substr(0, i);
      break;
    }
  }

  // Updating songInformation
  songInformation->SetLabel("\n" + song + "\n" + songExtension);

  // Initialize updateSlider
  updateSlider = new UpdateSlider(slider, mediaPlayer, playlist, songCache, shuffleOn, currentSong);

  mediaPlayer->Play();
}

void Controls::setPlaylist(SongList* playlistArg) { playlist = playlistArg; }

void Controls::toggleShuffle(wxCommandEvent& evt)
{
  if (shuffleOn == 0) shuffleOn = 1;
  else shuffleOn = 0;

  updateSlider->setShuffle(shuffleOn);
}

void Controls::previousSong(wxCommandEvent& evt)
{
  int songCacheSize = songCache.size();

  if (songCacheSize < 1) return;

  wxString newSong = songCache[songCacheSize - 1];
  songCache.pop_back();

  if (!mediaPlayer->Load(newSong)) { exit(1); }
}

void Controls::togglePlay(wxCommandEvent& evt)
{
  wxMediaState state = mediaPlayer->GetState();

  if (state == wxMEDIASTATE_PAUSED) mediaPlayer->Play();
  else if (state == wxMEDIASTATE_PLAYING) mediaPlayer->Pause();
}

void Controls::nextSong(wxCommandEvent& evt)
{
  if (mediaPlayer != nullptr) { delete mediaPlayer; mediaPlayer = nullptr; }

  #ifdef linux
    mediaPlayer = new wxMediaCtrl(this, MEDIA);
  #endif
  #ifdef _WIN32
    mediaPlayer = new wxMediaCtrl(
      this,
      MEDIA,
      wxEmptyString,
      wxDefaultPosition,
      wxDefaultSize,
      0,
      wxMEDIABACKEND_WMP10
    );
  #endif

  // Adding currentSong to the songCache
  songCache.push_back(currentSong);

  int nextSongIndex = 0;

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
        currentSong = currentSong.substr(i + 1);
        break;
      }
    }

    nextSongIndex = playlist->FindString(currentSong);
    if (nextSongIndex == (playlist->GetCount() - 1))
      nextSongIndex = 0;
    else
      nextSongIndex += 1;
  } else nextSongIndex = rand() % playlist->GetCount();

  playlist->SetSelection(nextSongIndex);

  // Getting the next song's file name + directory
  currentSong = playlist->GetString(nextSongIndex);
  currentSong = playlist->getPlaylistDirectory() + currentSong;

  if (!mediaPlayer->Load(currentSong)) { exit(1); }
}

