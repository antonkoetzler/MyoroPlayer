#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  // Menubar events
  EVT_MENU(wxID_EXIT, Frame::exit)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(1000, 800))
{
  menubar = new MenuBar();
  SetMenuBar(menubar);

  playlist = new SongList(this);

  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(playlist, 1, wxEXPAND);

  SetSizer(sizer);

  Centre();
}

Frame::~Frame() { Destroy(); }

void Frame::exit(wxCommandEvent& evt) { Close(); }
