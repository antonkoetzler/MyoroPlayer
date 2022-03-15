#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  // MenuBar events
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_MENU(SHOWCONTROLS, Frame::toggleControls)

  // Listbox events
  EVT_LISTBOX_DCLICK(SONGLIST, Frame::initSong)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(800, 600))
{
  menubar = new MenuBar();

  playlist = new SongList(this);
  controls = new Controls(this); controls->setPlaylist(playlist);
  controls->Show(false);

  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(playlist, 1, wxEXPAND);
  sizer->Add(controls, 0, wxEXPAND);

  SetMenuBar(menubar);
  SetSizer(sizer);
  Centre();
}

Frame::~Frame() { Destroy(); }

void Frame::exit(wxCommandEvent& evt) { Close(); }

void Frame::toggleControls(wxCommandEvent& evt)
{
  if (!controls->IsShown()) controls->Show(true);
  else controls->Show(false);
  sizer->Layout();
}

void Frame::initSong(wxCommandEvent& evt)
{
  // Making sure that controls are showing
  if (!controls->IsShown())
  {
    controls->Show(true);
    sizer->Layout();
  }

  // Gotta change this later
  wxString songDirectory = wxGetCwd();
  #ifdef linux
    songDirectory += "/songs/";
  #endif
  #ifdef _WIN32
    songDirectory += "\\songs\\";
  #endif
  songDirectory += evt.GetString();

  controls->initMediaPlayer(songDirectory);
}

