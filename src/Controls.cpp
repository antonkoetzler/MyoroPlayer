#include "Controls.h"

BEGIN_EVENT_TABLE(Controls, wxPanel)
  EVT_MEDIA_LOADED(MEDIA, Controls::playSong)
  EVT_SCROLL_THUMBRELEASE(Controls::changeCurrentTimePlaying)
//  EVT_BUTTON(PREVIOUS, Controls::previousSong)
  EVT_BUTTON(PLAY, Controls::togglePause)
//  EVT_BUTTON(NEXT, Controls::nextSong)
  EVT_BUTTON(SHUFFLE, Controls::toggleShuffle)
END_EVENT_TABLE()

Controls::Controls(wxFrame* parent, wxSize& size) : wxPanel(parent, wxID_ANY, wxDefaultPosition, size)
{
  slider = new wxSlider(
    this,
    SLIDER,
    0,
    0,
    1,
    wxDefaultPosition,
    wxSize(400, 30)
  );

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


  divider = new wxBoxSizer(wxHORIZONTAL);
  divider->AddStretchSpacer();
  divider->Add(mainControls, 0);
  divider->AddStretchSpacer();

  SetSizer(divider);
}

void Controls::setMediaPlayer(wxString songDirectory, SongList* playlistArg)
{
  playlist = playlistArg;

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
  }
  if (updateslider != nullptr)
  {
    delete updateslider; updateslider = nullptr;
  }

  if (!mediaPlayer->Load(songDirectory))
  {
    std::cout << "!mediaPlayer->Load()" << std::endl;
    exit(1);
  }

  updateslider = new UpdateSlider(slider, mediaPlayer, playlist);
}

void Controls::playSong(wxMediaEvent& evt)
{
  mediaPlayer->Play();
}

void Controls::changeCurrentTimePlaying(wxScrollEvent& evt)
{
  slider->SetValue(evt.GetPosition());
  mediaPlayer->Seek(evt.GetPosition() * 1000);
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
    case wxMEDIASTATE_STOPPED:
      // Plays the first song of the playlist
      wxString songName = playlist->GetString(0);
      #ifdef linux
        wxString songDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs/" + songName;
      #endif
      #ifdef _WIN32
        wxString songDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs\\" + songName;
      #endif
      setMediaPlayer(songDirectory, playlist);
      break;
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
