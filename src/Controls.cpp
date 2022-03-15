#include "Controls.h"

BEGIN_EVENT_TABLE(Controls, wxPanel)
  // Catching mediaPlayer->Load(...)
  EVT_MEDIA_LOADED(MEDIA, Controls::playSong)
END_EVENT_TABLE()

Controls::Controls(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1000, 90))
{
  songInformation = new wxStaticText(
    this,
    wxID_ANY,
    "\nSong Name\nSong Extension",
    wxDefaultPosition,
    wxSize(190, 75),
    wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE | wxST_ELLIPSIZE_END
  );
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
    wxID_ANY,
    "%",
    wxDefaultPosition,
    wxSize(40, 40),
    wxBORDER_NONE
  );
  previous = new wxButton(
    this,
    wxID_ANY,
    "<<",
    wxDefaultPosition,
    wxSize(40, 40),
    wxBORDER_NONE
  );
  play = new wxButton(
    this,
    wxID_ANY,
    ">",
    wxDefaultPosition,
    wxSize(40, 40),
    wxBORDER_NONE
  );
  next = new wxButton(
    this,
    wxID_ANY,
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

  if (!mediaPlayer->Load(songDirectory)) { exit(1); }
}

void Controls::playSong(wxMediaEvent& evt)
{
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

  mediaPlayer->Play();
}

void Controls::setPlaylist(SongList* playlistArg) { playlist = playlistArg; }

