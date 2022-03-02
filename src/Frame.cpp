#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  // Menubar events
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_MENU(SHOWCONTROLS, Frame::showControls)

  // Playlist events
  EVT_LISTBOX_DCLICK(SONGLIST, Frame::setControls)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(1000, 800))
{
  menubar = new MenuBar();
  SetMenuBar(menubar);

  playlist = new SongList(this);

  controls = new Controls(this);
  controls->Show(false);

  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(playlist, 1, wxEXPAND);
  sizer->Add(controls, 0, wxEXPAND);

  SetSizer(sizer);

  Centre();
}

Frame::~Frame() { Destroy(); }

void Frame::exit(wxCommandEvent& evt) { Close(); }

void Frame::showControls(wxCommandEvent& evt)
{
  if (controls->IsShown()) controls->Show(false);
  else controls->Show(true);

  sizer->Layout();
}

void Frame::setControls(wxCommandEvent& evt)
{
  std::cout << "Hello" << std::endl;
}
