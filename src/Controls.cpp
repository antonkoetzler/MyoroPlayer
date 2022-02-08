#include "Controls.h"

Controls::Controls(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1400, 70))
{
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

  divider = new wxBoxSizer(wxHORIZONTAL);

  divider->AddStretchSpacer(); // Adds 'whitespace'; used for centering

  divider->Add(
    playControls,
    0
  );

  divider->AddStretchSpacer();

  SetSizer(divider);
}
