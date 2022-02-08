#include "Frame.h"

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(1400, 800))
{
  Center();

  ui = new wxBoxSizer(wxVERTICAL);

  songlist = new SongList(this);
  ui->Add(
    songlist,
    1,
    wxEXPAND
  );

  controls = new Controls(this);
  ui->Add(
    controls,
    0,
    wxEXPAND
  );

  menubar = new MenuBar();

  SetSizer(ui);
  SetMenuBar(menubar);
}

Frame::~Frame() { this->Destroy(); }

