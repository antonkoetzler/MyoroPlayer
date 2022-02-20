#include "Controls.h"

BEGIN_EVENT_TABLE(Controls, wxPanel)
  EVT_MEDIA_LOADED(MEDIA, Controls::playSong)
END_EVENT_TABLE()

Controls::Controls(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1400, 85))
{
  // Allocating playControls
  playControls = new wxBoxSizer(wxVERTICAL);

  songSlider = new wxSlider(
    this,
    wxID_ANY,
    0,
    0,
    1,
    wxDefaultPosition,
    wxSize(200, 25)
  );
  playControls->Add(
    songSlider,
    0,
    wxALL,
    5
  );

  // Allocating playControlsButtons
  playControlsButtons = new wxBoxSizer(wxHORIZONTAL);

  // Loading images onto the bitmap buttons
  wxImage::AddHandler(new wxPNGHandler); // Initialize wxWidgets PNG handler
  wxBitmap imgBitmap;
  wxLogNull errorWorkaround; // Supressing a warning coming from the PNG handler
                             // Just initializing this variable prevents errors, nothing else needs to be done

  imgBitmap.LoadFile("../img/shuffle.png", wxBITMAP_TYPE_PNG);
  if (!imgBitmap.IsOk())
  {
    std::cout << "Error loading shuffle.png" << std::endl;
    Close(true);
  }

  shuffle = new wxBitmapButton(
    this,
    wxID_ANY,
    imgBitmap,
    wxDefaultPosition,
    wxSize(40, 40)
  );
  playControlsButtons->Add(
    shuffle,
    0,
    wxRIGHT,
    5
  );

  imgBitmap.LoadFile("../img/playPrevious.png", wxBITMAP_TYPE_PNG);
  if (!imgBitmap.IsOk())
  {
    std::cout << "Error loading playPrevious.png" << std::endl;
    Close(true);
  }

  playPrevious = new wxBitmapButton(
    this,
    wxID_ANY,
    imgBitmap,
    wxDefaultPosition,
    wxSize(40, 40)
  );
  playControlsButtons->Add(
    playPrevious,
    0,
    wxRIGHT,
    5
  );

  imgBitmap.LoadFile("../img/play.png", wxBITMAP_TYPE_PNG);
  if (!imgBitmap.IsOk())
  {
    std::cout << "Error loading play.png" << std::endl;
    Close(true);
  }

  playButton = new wxBitmapButton(
    this,
    wxID_ANY,
    imgBitmap,
    wxDefaultPosition,
    wxSize(40, 40)
  );
  playControlsButtons->Add(
    playButton,
    0,
    wxRIGHT,
    5
  );

  imgBitmap.LoadFile("../img/playNext.png", wxBITMAP_TYPE_PNG);
  if (!imgBitmap.IsOk())
  {
    std::cout << "Error loading playNext.png" << std::endl;
    Close(true);
  }

  playNext = new wxBitmapButton(
    this,
    wxID_ANY,
    imgBitmap,
    wxDefaultPosition,
    wxSize(40, 40)
  );
  playControlsButtons->Add(
    playNext,
    0
  );

  playControls->Add(
    playControlsButtons,
    0,
    wxALIGN_CENTRE
  );

  // Allocating divider
  divider = new wxBoxSizer(wxHORIZONTAL);
  divider->AddStretchSpacer(); // Adds 'whitespace'; used for centering
  divider->Add(
    playControls,
    0
  );
  divider->AddStretchSpacer();

  SetSizer(divider);
}

void Controls::loadSong(wxString songDirectory, SongList* songlist)
{
  if (playlist != nullptr) { playlist = nullptr; playlist = songlist; }
  if (mediaPlayer != nullptr) { delete mediaPlayer; mediaPlayer = nullptr; }

  songCache.push_back(songDirectory);

  mediaPlayer = new wxMediaCtrl(
    this,
    MEDIA,
    wxEmptyString,
    wxDefaultPosition,
    wxDefaultSize,
    0,
    wxMEDIABACKEND_WMP10
  );
  if (mediaPlayer->Load(songDirectory)) mediaPlayer->Play();
}

void Controls::playSong(wxMediaEvent& evt) { mediaPlayer->Play(); }
