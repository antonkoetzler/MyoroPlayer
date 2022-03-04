#include "Controls.h"

BEGIN_EVENT_TABLE(Controls, wxPanel)
  // Catching event after mediaPlayer->Load(...)
  EVT_MEDIA_LOADED(MEDIA, Controls::playSong)

  // Slider(s') event
  EVT_SCROLL_THUMBRELEASE(Controls::changeSliderPosition)

  // Music controls (play/pause, shuffle, next, previous)
  EVT_BUTTON(SHUFFLE, Controls::toggleShuffle)
  EVT_BUTTON(PREVIOUS, Controls::previousSong)
  EVT_BUTTON(PLAY, Controls::togglePause)
  EVT_BUTTON(NEXT, Controls::nextSong)
END_EVENT_TABLE()

Controls::Controls(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1000, 90))
{
  setMusicControls();
  setSongInformation();

  volume = new wxSlider(
    this,
    VOLUME,
    100,
    0,
    100,
    wxDefaultPosition,
    wxSize(210, 35)
  );

  divider = new wxBoxSizer(wxHORIZONTAL);
  divider->Add(songInformation, 0);
  divider->AddStretchSpacer();
  divider->Add(musicControls, 0);
  divider->AddStretchSpacer();
  divider->Add(volume, 0, wxALIGN_CENTRE);

  SetSizer(divider);
}

void Controls::setMusicControls()
{
  // Slider
  #ifdef linux
    slider = new wxSlider(
      this,
      SLIDER,
      10,
      0,
      100,
      wxDefaultPosition,
      wxSize(350, 40)
    );
  #endif
  #ifdef _WIN32
    slider = new wxSlider(
      this,
      SLIDER,
      10,
      0,
      100,
      wxDefaultPosition,
      wxSize(350, 30)
    );
  #endif

  // Buttons
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
    PREVIOUS,
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

  buttons = new wxBoxSizer(wxHORIZONTAL);
  buttons->Add(shuffle, 0, wxRIGHT, 10);
  buttons->Add(previous, 0, wxRIGHT, 10);
  buttons->Add(play, 0, wxRIGHT, 10);
  buttons->Add(next, 0);

  // Sizer
  musicControls = new wxBoxSizer(wxVERTICAL);
  #ifdef linux
    musicControls->Add(slider, 0, wxTOP, 5);
  #endif
  #ifdef _WIN32
    musicControls->Add(slider, 0, wxALL, 5);
  #endif
  musicControls->Add(buttons, 0, wxALIGN_CENTRE);
}

void Controls::setSongInformation()
{
  // Setting up songCover
  wxImage::AddHandler(new wxPNGHandler);

  wxBitmap image;
  #ifdef linux
    image.LoadFile("../img/musicNote.png", wxBITMAP_TYPE_PNG);
  #endif
  #ifdef _WIN32
    image.LoadFile("..\\img\\musicNote.png", wxBITMAP_TYPE_PNG);
  #endif

  if (!image.IsOk())
  {
    std::cout << "!image.IsOk()" << std::endl;
    exit(1);
  }

  songCover = new wxStaticBitmap(
    this,
    wxID_ANY,
    image
  );

  // Setting up fileDetails
  fileDetails = new wxStaticText(
    this,
    wxID_ANY,
    "Song Name\nSong Extension",
    wxDefaultPosition,
    wxSize(120, 40)
  );
  fileDetails->SetFont(
    wxFont(
      12,
      wxFONTFAMILY_DEFAULT,
      wxFONTSTYLE_NORMAL,
      wxFONTWEIGHT_NORMAL
    )
  );

  // Setting up songInformation
  songInformation = new wxBoxSizer(wxHORIZONTAL);
  songInformation->Add(songCover, 0, wxLEFT | wxTOP | wxRIGHT, 5);
  songInformation->Add(fileDetails, 0, wxALIGN_CENTER_VERTICAL);
}

void Controls::setMediaPlayer(wxString songDirectory)
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

  if (!mediaPlayer->Load(songDirectory))
  {
    std::cout << "!mediaPlayer->Load(songDirectory)\n";
    exit(1);
  }
}

void Controls::playSong(wxMediaEvent& evt)
{
  if (updateslider != nullptr) { delete updateslider; updateslider = nullptr; }

  wxString song = playlist->GetString(playlist->GetSelection());
  wxString songExtension;

  // Getting the song's file extension and name (without file extension)
  for (int i = (song.length() - 1); i >= 0; i--)
  {
    if (song[i] == '.')
    {
      songExtension = song.substr(i + 1);
      song = song.substr(0, i);
      break;
    }
  }

  // Updating songInformation sizer
  if (song.length() > 20)
    song = song.substr(0, 20);
  fileDetails->SetLabel(song + "\n" + songExtension);

  // Setting up the timer to keep track of slider
  updateslider = new UpdateSlider(slider, mediaPlayer, playlist, shuffleToggle, songCache, queue, playlistDirectory);

  mediaPlayer->Play();
}

void Controls::setPlaylist(SongList* playlistArg) { playlist = playlistArg; }

void Controls::addToSongCache(wxString songDirectory) { songCache.push_back(songDirectory); }

void Controls::changeSliderPosition(wxScrollEvent& evt)
{
  switch (evt.GetId())
  {
    case SLIDER:
      slider->SetValue(evt.GetPosition());
      mediaPlayer->Seek(evt.GetPosition() * 1000);
      break;
    case VOLUME:
      volume->SetValue(evt.GetPosition());
      double volume = (double)evt.GetPosition() / 100;
      mediaPlayer->SetVolume(volume);
      break;
  }
}

void Controls::toggleShuffle(wxCommandEvent& evt)
{
  if (shuffleToggle == 0) shuffleToggle = 1;
  else shuffleToggle = 0;
}

void Controls::previousSong(wxCommandEvent& evt)
{
  int songCacheSize = songCache.size();
  bool cont = false;

  if (songCacheSize >= 2)
  {
    songCache.pop_back();
    cont = true;
  }

  if (cont)
  {
    // Need the song's file name
    wxString song = songCache[songCache.size() - 1];
    // Removing directory from var song
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

    // Changing selection
    playlist->SetSelection(playlist->FindString(song));

    if (!mediaPlayer->Load(songCache[songCache.size() - 1]))
    {
      std::cout << "!mediaPlayer->Load(songCache[songCache.size() - 1])" << std::endl;
      exit(1);
    }

    // Removing the now previous song that is playing
    songCache.pop_back();
  }
}

void Controls::togglePause(wxCommandEvent& evt)
{
  wxMediaState state = mediaPlayer->GetState();

  switch (state)
  {
    case wxMEDIASTATE_PLAYING:
      mediaPlayer->Pause();
      break;
    case wxMEDIASTATE_PAUSED:
      mediaPlayer->Play();
      break;
  }
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
    // Need to get the song's position in playlist to determine what plays next

    // Getting the current song
    wxString currentSong = songCache[songCache.size() - 1];
    // Removing the directory of the song
    for (int i = (currentSong.length() - 1); i >= 0; i--)
    {
      #ifdef linux
        if (currentSong[i] == '/')
        {
          currentSong = currentSong.substr(i + 1);
          break;
        }
      #endif
      #ifdef _WIN32
        if (currentSong[i] == '\\')
        {
          currentSong = currentSong.substr(i + 1);
          break;
        }
      #endif
    }

    nextSongIndex = playlist->FindString(currentSong);
    if (nextSongIndex == (playlist->GetCount() - 1))
      nextSongIndex = 0;
    else
      nextSongIndex += 1;
  }
  else
    nextSongIndex = rand() % playlist->GetCount();

  playlist->SetSelection(nextSongIndex); // Highlighting song on the playlist list

  // Getting the next song's file name + directory
  wxString songDirectory = playlist->GetString(nextSongIndex);
  songDirectory = playlistDirectory + songDirectory;

  songCache.push_back(songDirectory);

  if (!mediaPlayer->Load(songDirectory))
  {
    std::cout << "!mediaPlayer->Load(songDirectory)" << std::endl;
    exit(1);
  }
}

void Controls::setPlaylistDirectory(wxString playlistDirectoryArg) { playlistDirectory = playlistDirectoryArg; }

void Controls::addToQueue(wxString song)
{
  queue.push_back(song);
  if (updateslider != nullptr) updateslider->setQueue(queue);
}
