#include "Controls.h"

BEGIN_EVENT_TABLE(Controls, wxPanel)
  EVT_MEDIA_LOADED(MEDIA, Controls::playSong)
END_EVENT_TABLE()

Controls::Controls(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1000, 90))
{
  setMusicControls();
  setSongInformation();

  volume = new wxSlider(
    this,
    wxID_ANY,
    10,
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
      wxID_ANY,
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
      wxID_ANY,
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

  mediaPlayer->Play();
}

void Controls::setPlaylist(SongList* playlistArg) { playlist = playlistArg; }
