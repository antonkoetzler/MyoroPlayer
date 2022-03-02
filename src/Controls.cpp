#include "Controls.h"

Controls::Controls(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1000, 90))
{
  setMusicControls();

  divider = new wxBoxSizer(wxHORIZONTAL);
  divider->AddStretchSpacer();
  divider->Add(musicControls, 0);
  divider->AddStretchSpacer();

  SetSizer(divider);
}

void Controls::setMusicControls()
{
  // Slider
  slider = new wxSlider(
    this,
    wxID_ANY,
    10,
    0,
    100,
    wxDefaultPosition,
    wxSize(350, 30)
  );

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
  musicControls->Add(slider, 0, wxALL, 5);
  musicControls->Add(buttons, 0, wxALIGN_CENTRE);
}
