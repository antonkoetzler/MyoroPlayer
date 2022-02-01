#include "Frame.h"

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(1400, 800))
{
  Center();

  ui = new wxBoxSizer(wxVERTICAL);

  sl = new SongList(this);
  ui->Add(
    sl,
    1,
    wxEXPAND
  );

  SetSizer(ui);
}

Frame::~Frame() { this->Destroy(); }

