#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU(wxID_EXIT, Frame::quit)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(800, 600))
{
  menubar = new MenuBar();
  SetMenuBar(menubar);

  sidebar = new SideBar(this);
  songlist = new SongList(this);
  controls = new Controls(this);

  songSizer = new wxBoxSizer(wxVERTICAL);
  songSizer->Add(songlist, 1, wxEXPAND);
  songSizer->Add(controls, 0, wxEXPAND);

  sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->Add(sidebar, 0, wxEXPAND);
  sizer->Add(songSizer, 1, wxEXPAND);
  SetSizer(sizer);
}

Frame::~Frame() { Destroy(); }

void Frame::quit(wxCommandEvent& evt) { exit(0); }
