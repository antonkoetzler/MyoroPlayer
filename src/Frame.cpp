#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_LISTBOX_DCLICK(SONGLIST, Frame::setControls)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(1000, 800))
{
  Centre();

  menubar = new MenuBar();
  SetMenuBar(menubar);

  playlist = new SongList(this);

  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(playlist, 1, wxEXPAND);
  SetSizer(sizer);
}

Frame::~Frame() { Destroy(); }

void Frame::exit(wxCommandEvent& evt) { Close(); }

void Frame::setControls(wxCommandEvent& evt)
{
  if (controls == nullptr)
  {
    wxSize controlsSize = wxSize(GetSize().GetWidth(), 115);
    controls = new Controls(this, controlsSize);
    sizer->Add(controls, 0, wxEXPAND);
    sizer->Layout();
  }

  #ifdef linux
    wxString songDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs/" + evt.GetString();
  #endif
  #ifdef _WIN32
    wxString songDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs\\" + evt.GetString();
  #endif

  controls->setMediaPlayer(songDirectory, playlist);
}
