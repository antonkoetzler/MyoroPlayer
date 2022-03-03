#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  // Menubar events
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_MENU(SHOWCONTROLS, Frame::showControls)
  EVT_MENU(SETDIR, Frame::showSetDirectory)

  // Playlist events
  EVT_LISTBOX_DCLICK(SONGLIST, Frame::setControls)

  // popupWindow events
  EVT_TEXT_ENTER(SETDIRINPUT, Frame::setDirectory)
  EVT_BUTTON(SETDIRBUTTON, Frame::setDirectory)
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
  std::cout << evt.GetString() << std::endl;
}

void Frame::showSetDirectory(wxCommandEvent& evt)
{
  popupWindow = new wxFrame(
    this,
    wxID_ANY,
    "Set Directory/Playlist"
  );

  input = new wxTextCtrl(
    popupWindow,
    SETDIRINPUT,
    wxEmptyString,
    wxDefaultPosition,
    wxSize(250, 30),
    wxTE_CENTRE | wxTE_PROCESS_ENTER
  );

  button = new wxButton(
    popupWindow,
    SETDIRBUTTON,
    "Set New Directory",
    wxDefaultPosition,
    wxDefaultSize,
    wxBORDER_NONE
  );

  wxBoxSizer* popupWindowSizer = new wxBoxSizer(wxVERTICAL);
  popupWindowSizer->Add(input, 0, wxEXPAND);
  popupWindowSizer->Add(button, 0, wxEXPAND);
  popupWindow->SetSizerAndFit(popupWindowSizer);

  popupWindow->Show(true);
  popupWindow->Centre();

  input->SetFocus();
}

void Frame::setDirectory(wxCommandEvent& evt)
{
  wxString newDirectory = input->GetLineText(0);
  // Adding a slash to string if it doesn't have one at the end
  #ifdef linux
    if (newDirectory[newDirectory.length() - 1] != '/')
      newDirectory += '/';
  #endif
  #ifdef _WIN32
    if (newDirectory[newDirectory.length() - 1] != '\\')
      newDirectory += '\\';
  #endif

  // Checking if the directory is valid
  wxDir* dirTest = new wxDir(newDirectory);
  if (dirTest->IsOpened())
  {
    playlistDirectory = newDirectory;

    sizer->Clear(false);

    delete playlist; playlist = nullptr;

    playlist = new SongList(this, playlistDirectory);

    sizer->Add(playlist, 1, wxEXPAND);
    sizer->Add(controls, 0, wxEXPAND);
    sizer->Layout();

    if (popupWindow != nullptr)
    {
      popupWindow->Close();
      delete popupWindow; popupWindow = nullptr;
    }
  }

  delete dirTest; dirTest = nullptr;
}
