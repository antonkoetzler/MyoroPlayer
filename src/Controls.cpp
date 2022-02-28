#include "Controls.h"

BEGIN_EVENT_TABLE(Controls, wxPanel)
  EVT_MEDIA_LOADED(MEDIA, Controls::playSong)
  EVT_SCROLL_THUMBRELEASE(Controls::changeCurrentTimePlaying)
  EVT_BUTTON(PREVIOUS, Controls::previousSong)
  EVT_BUTTON(PLAY, Controls::togglePause)
  EVT_BUTTON(NEXT, Controls::nextSong)
  EVT_BUTTON(SHUFFLE, Controls::toggleShuffle)
END_EVENT_TABLE()

Controls::Controls(wxFrame* parent, wxSize& size) : wxPanel(parent, wxID_ANY, wxDefaultPosition, size)
{
  songDetailsContainer = new wxPanel(
    this,
    wxID_ANY,
    wxDefaultPosition,
    wxSize(300, 115)
  );

  // Need to init PNG image handler
  wxImage::AddHandler(new wxPNGHandler);
  wxBitmap image;
  #ifdef linux
    image.LoadFile("../img/musicNote.png", wxBITMAP_TYPE_PNG);
  #endif
  #ifdef _WIN32
    image.LoadFile("..\\img\\musicNote.png", wxBITMAP_TYPE_PNG);
  #endif

  if (image.IsOk())
    musicNote = new wxStaticBitmap(songDetailsContainer, wxID_ANY, image);

  details = new wxStaticText(
    songDetailsContainer,
    wxID_ANY,
    "Song Name\nSong File Extension",
    wxDefaultPosition,
    wxSize(200, 50),
    wxALIGN_LEFT
  );
  details->SetFont(
    wxFont(
      12,
      wxFONTFAMILY_MODERN,
      wxFONTSTYLE_NORMAL,
      wxFONTWEIGHT_NORMAL
    )
  );

  songDetailsSizer = new wxBoxSizer(wxHORIZONTAL);
  songDetailsSizer->Add(musicNote, 0, wxALIGN_CENTRE);
  songDetailsSizer->Add(details, 0, wxALL | wxALIGN_CENTRE_VERTICAL);

  songDetailsContainer->SetSizer(songDetailsSizer);

  #ifdef linux
    slider = new wxSlider(
      this,
      SLIDER,
      0,
      0,
      1,
      wxDefaultPosition,
      wxSize(400, 40)
    );
  #endif
  #ifdef _WIN32
    slider = new wxSlider(
      this,
      SLIDER,
      0,
      0,
      1,
      wxDefaultPosition,
      wxSize(400, 30)
    );
  #endif

  shuffle = new wxButton(
    this,
    SHUFFLE,
    "%",
    wxDefaultPosition,
    wxSize(50, 50)
  );
  previous = new wxButton(
    this,
    PREVIOUS,
    "<<",
    wxDefaultPosition,
    wxSize(50, 50)
  );
  play = new wxButton(
    this,
    PLAY,
    ">",
    wxDefaultPosition,
    wxSize(50, 50)
  );
  next = new wxButton(
    this,
    NEXT,
    ">>",
    wxDefaultPosition,
    wxSize(50, 50)
  );

  mainControlsButtons = new wxBoxSizer(wxHORIZONTAL);
  mainControlsButtons->Add(
    shuffle,
    0,
    wxRIGHT | wxALIGN_CENTRE,
    5
  );
  mainControlsButtons->Add(
    previous,
    0,
    wxRIGHT | wxALIGN_CENTRE,
    5
  );
  mainControlsButtons->Add(
    play,
    0,
    wxRIGHT | wxALIGN_CENTRE,
    5
  );
  mainControlsButtons->Add(
    next,
    0,
    wxALIGN_CENTRE
  );

  mainControls = new wxBoxSizer(wxVERTICAL);
  mainControls->Add(
    slider,
    0,
    wxALL | wxALIGN_CENTRE,
    10
  );
  mainControls->Add(
    mainControlsButtons,
    0,
    wxALL | wxALIGN_CENTRE
  );

  volume = new wxSlider(
    this,
    VOLUME,
    100,
    0,
    100,
    wxDefaultPosition,
    wxSize(250, 50)
  );
  divider = new wxBoxSizer(wxHORIZONTAL);
  divider->Add(songDetailsContainer, 0);
  divider->AddStretchSpacer();
  divider->Add(mainControls, 0);
  divider->AddStretchSpacer();
  divider->Add(volume, 0, wxALIGN_CENTRE);

  SetSizer(divider);
}

void Controls::setMediaPlayer(wxString songDirectory, SongList* playlistArg)
{
  playlist = playlistArg;

  // Intializing mediaPlayer
  if (mediaPlayer == nullptr)
  {
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
  }
  if (updateslider != nullptr)
  {
    delete updateslider; updateslider = nullptr;
  }

  // Adding song to cache
  songCache.push_back(songDirectory);

  // Loading song
  if (!mediaPlayer->Load(songDirectory))
  {
    std::cout << "!mediaPlayer->Load()" << std::endl;
    exit(1);
  }

  updateslider = new UpdateSlider(slider, mediaPlayer, playlist);
}

void Controls::playSong(wxMediaEvent& evt)
{
  // Updating the song name and extension
  // Parsing the string
  wxString song = playlist->GetString(playlist->GetSelection());
  wxString songExtension;
  // Grabbing the extension and parsing
  // song to only be the song name
  for (int i = (song.length() - 1); i >= 0; i--)
  {
    if (song[i] == '.')
    {
      songExtension = song.substr(i + 1);
      song = song.substr(0, i);
      break;
    }
  }

  if (song.length() > 40)
    details->SetLabel(song);
  else
    details->SetLabel(song + "\n" + songExtension);

  // Checking if this is loaded from a UpdateSlider call
  if (updateslider->getTempSongDirectory() != wxEmptyString)
    songCache.push_back(updateslider->getTempSongDirectory());

  mediaPlayer->Play();
}

void Controls::changeCurrentTimePlaying(wxScrollEvent& evt)
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

void Controls::previousSong(wxCommandEvent& evt)
{
  if (songCache.size() != 0)
  {
    if (!mediaPlayer->Load(songCache[songCache.size() - 1]))
      std::cout << "!mediaPlayer->Load(...)" << std::endl;
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
  if (playlist != nullptr)
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

      #ifdef linux
        songDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs/" + songName;
      #endif
      #ifdef _WIN32
        songDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs\\" + songName;
      #endif
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

    songCache.push_back(songDirectory);

    if (!mediaPlayer->Load(songDirectory))
    {
      std::cout << "!mediaPlayer->Load(songDirectory)" << std::endl;
      exit(1);
    }
  }
}

void Controls::toggleShuffle(wxCommandEvent& evt)
{
  switch (shuffleToggle)
  {
    case 0:
      shuffleToggle = 1;
      break;
    case 1:
      shuffleToggle = 0;
      break;
  }

  if (updateslider)
    updateslider->setShuffleToggle(shuffleToggle);
}

void Controls::setQueue(wxVector<wxString> queueArg)
{
  for (size_t i = 0; i < queueArg.size(); i++)
    queue.push_back(queueArg[i]);
  updateslider->setQueue(queue);
}
