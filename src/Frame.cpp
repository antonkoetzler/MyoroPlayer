#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_MENU(SETDIR, Frame::showSetDirectory)
  EVT_LISTBOX_DCLICK(SONGLIST, Frame::setControls)
  EVT_BUTTON(SETDIRBUTTON, Frame::setDirectory)
  EVT_TEXT_ENTER(SETDIRINPUT, Frame::setDirectory)
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

void Frame::showSetDirectory(wxCommandEvent& evt)
{
  // Creating the window
  setDirectoryWindow = new wxFrame(
    this,
    wxID_ANY,
    "Set Directory",
    wxDefaultPosition,
    wxSize(250, 70)
  );
  setDirectoryWindow->Show(true);
  setDirectoryWindow->Centre();

  // Creating window controls
  setDirectorySizer = new wxBoxSizer(wxVERTICAL);

  setDirectoryInput = new wxTextCtrl(
    setDirectoryWindow,
    SETDIRINPUT,
    wxEmptyString,
    wxDefaultPosition,
    wxSize(250, 40),
    wxTE_CENTRE | wxBORDER_NONE | wxTE_PROCESS_ENTER
  ); 
  setDirectoryButton = new wxButton(
    setDirectoryWindow,
    SETDIRBUTTON,
    "Set Directory",
    wxDefaultPosition,
    wxSize(250, 30),
    wxBORDER_NONE
  );

  setDirectorySizer->Add(setDirectoryInput, 0, wxEXPAND);
  setDirectorySizer->Add(setDirectoryButton, 0, wxEXPAND);

  setDirectoryWindow->SetSizerAndFit(setDirectorySizer);

  setDirectoryInput->SetFocus();
}

void Frame::setDirectory(wxCommandEvent& evt)
{
  delete playlist; playlist = nullptr;
  playlist = new SongList(this, setDirectoryInput->GetLineText(0));

  sizer->Clear(false);
  sizer->Add(playlist, 1, wxEXPAND);
  sizer->Add(controls, 0, wxEXPAND);
  sizer->Layout();
}
