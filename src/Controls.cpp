#include "Controls.h"

Controls::Controls(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1400, 75))
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

  shuffle = new wxButton(
    this,
    wxID_ANY,
    wxEmptyString,
    wxDefaultPosition,
    wxSize(30, 30)
  );
  playControlsButtons->Add(
    shuffle,
    0,
    wxRIGHT,
    5
  );

  playPrevious = new wxButton(
    this,
    wxID_ANY,
    wxEmptyString,
    wxDefaultPosition,
    wxSize(30, 30)
  );
  playControlsButtons->Add(
    playPrevious,
    0,
    wxRIGHT,
    5
  );

  playButton = new wxButton(
    this,
    wxID_ANY,
    wxEmptyString,
    wxDefaultPosition,
    wxSize(30, 30)
  );
  playControlsButtons->Add(
    playButton,
    0,
    wxRIGHT,
    5
  );

  playNext = new wxButton(
    this,
    wxID_ANY,
    wxEmptyString,
    wxDefaultPosition,
    wxSize(30, 30)
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
