#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_LISTBOX_DCLICK(SONGLIST, Frame::getSongAndPlaylist)
END_EVENT_TABLE()

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

void Frame::getSongAndPlaylist(wxCommandEvent& evt)
{
  // Gotta change this to use other directories
  #ifdef _WIN32
    wxString songDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs\\" + evt.GetString();
  #endif
  
  #ifdef linux
    wxString songDirectory = wxGetCwd().substr(0, wxGetCwd().length() - 5) + "songs/" + evt.GetString();
  #endif
  
  controls->loadSong(songDirectory, songlist);
}
