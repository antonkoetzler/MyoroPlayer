#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  // Menu events
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_MENU(SHOWCONTROLS, Frame::showControls)
  EVT_MENU(SETDIR, Frame::showSetDirectory)
  EVT_MENU(YT2MP3, Frame::showYt2Mp3)

  // Playlist/SongList events
  EVT_LISTBOX_DCLICK(SONGLIST, Frame::setControls)

  // Song right click menu events
  EVT_MENU(QUEUE, Frame::addToQueue)

  // Set directory events
  EVT_BUTTON(SETDIRBUTTON, Frame::setDirectory)
  EVT_BUTTON(YT2MP3BUTTON, Frame::Yt2Mp3)
  EVT_TEXT_ENTER(SETDIRINPUT, Frame::setDirectory)
  EVT_TEXT_ENTER(YT2MP3INPUT, Frame::Yt2Mp3)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(1000, 800))
{
  Centre();

  menubar = new MenuBar();
  SetMenuBar(menubar);

  playlist = new SongList(this);

  wxSize controlsSize = wxSize(GetSize().GetWidth(), 115);
  controls = new Controls(this, controlsSize, playlistDirectory);
  controls->Hide();

  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(playlist, 1, wxEXPAND);
  SetSizer(sizer);

  // Cannot set the event in the event table
  playlist->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(Frame::songMenu), nullptr, this);
}

Frame::~Frame() { Destroy(); }

void Frame::exit(wxCommandEvent& evt) { Close(); }

void Frame::setControls(wxCommandEvent& evt)
{
  if (sizer->GetItemCount() == 1)
  {
    controls->Show(true);
    sizer->Add(controls, 0, wxEXPAND);
    sizer->Layout();
  }

  wxString songDirectory = playlistDirectory + evt.GetString();

  controls->setMediaPlayer(songDirectory, playlist);
}

void Frame::showSetDirectory(wxCommandEvent& evt)
{
  // Creating the window
  setterWindow = new wxFrame(
    this,
    wxID_ANY,
    "Set Directory",
    wxDefaultPosition,
    wxSize(250, 70)
  );
  setterWindow->Show(true);
  setterWindow->Centre();

  // Creating window controls
  setterWindowSizer = new wxBoxSizer(wxVERTICAL);

  setterWindowInput = new wxTextCtrl(
    setterWindow,
    SETDIRINPUT,
    wxEmptyString,
    wxDefaultPosition,
    wxSize(250, 20),
    wxTE_CENTRE | wxBORDER_NONE | wxTE_PROCESS_ENTER | wxTE_CENTRE
  ); 
  setterWindowButton = new wxButton(
    setterWindow,
    SETDIRBUTTON,
    "Set Directory",
    wxDefaultPosition,
    wxSize(250, 30),
    wxBORDER_NONE
  );

  setterWindowSizer->Add(setterWindowInput, 0, wxEXPAND);
  setterWindowSizer->Add(setterWindowButton, 0, wxEXPAND);

  setterWindow->SetSizerAndFit(setterWindowSizer);

  setterWindowInput->SetFocus();
}

void Frame::setDirectory(wxCommandEvent& evt)
{
  bool setControls;
  if (sizer->GetItemCount() == 2)
    setControls = true;
  else
    setControls = false;

  delete playlist; playlist = nullptr;
  playlist = new SongList(this, setterWindowInput->GetLineText(0));

  #ifdef linux
    if (setterWindowInput->GetLineText(0)[setterWindowInput->GetLineText(0).length() - 1] != '/')
      playlistDirectory = setterWindowInput->GetLineText(0) + '/';
  #endif
  #ifdef _WIN32
    if (setterWindowInput->GetLineText(0)[setterWindowInput->GetLineText(0).length() - 1] != '\\')
      playlistDirectory = setterWindowInput->GetLineText(0) + '\\';
  #endif
    else
      playlistDirectory = setterWindowInput->GetLineText(0);
  

  sizer->Clear(false);
  sizer->Add(playlist, 1, wxEXPAND);
  if (setControls) sizer->Add(controls, 0, wxEXPAND);
  sizer->Layout();

  setterWindow->Close();
  delete setterWindow; setterWindow = nullptr;
}

void Frame::showControls(wxCommandEvent& evt)
{
  if (sizer->GetItemCount() == 2)
  {
    sizer->Detach(controls);
    controls->Hide();
    sizer->Layout();
  }
  else
  {
    controls->Show(true);
    sizer->Add(controls, 0, wxEXPAND);
    sizer->Layout();
  }
}

void Frame::songMenu(wxMouseEvent& evt)
{
  wxClientDC dc(this);
  playlist->SetSelection(playlist->HitTest(evt.GetLogicalPosition(dc)));

  wxMenuItem* popupQueue = new wxMenuItem(
    nullptr,
    QUEUE,
    "Queue song"
  );

  wxMenu* popup = new wxMenu();
  popup->Append(popupQueue);

  PopupMenu(popup, wxDefaultPosition);
}

void Frame::addToQueue(wxCommandEvent& evt)
{
  wxString songName = playlist->GetString(playlist->GetSelection());

  wxString songDirectory = playlistDirectory + songName;

  queue.push_back(songDirectory);
  controls->setQueue(queue);
}

void Frame::showYt2Mp3(wxCommandEvent& evt)
{
  // Creating the window
  setterWindow = new wxFrame(
    this,
    wxID_ANY,
    "Convert YouTube Link to MP3",
    wxDefaultPosition,
    wxSize(250, 70)
  );
  setterWindow->Show(true);
  setterWindow->Centre();

  // Creating window controls
  setterWindowSizer = new wxBoxSizer(wxVERTICAL);

  setterWindowInput = new wxTextCtrl(
    setterWindow,
    YT2MP3INPUT,
    wxEmptyString,
    wxDefaultPosition,
    wxSize(250, 20),
    wxTE_CENTRE | wxBORDER_NONE | wxTE_PROCESS_ENTER | wxTE_CENTRE
  ); 
  setterWindowButton = new wxButton(
    setterWindow,
    YT2MP3BUTTON,
    "Convert to MP3",
    wxDefaultPosition,
    wxSize(250, 30),
    wxBORDER_NONE
  );

  setterWindowSizer->Add(setterWindowInput, 0, wxEXPAND);
  setterWindowSizer->Add(setterWindowButton, 0, wxEXPAND);

  setterWindow->SetSizerAndFit(setterWindowSizer);

  setterWindowInput->SetFocus();
}

void Frame::Yt2Mp3(wxCommandEvent& evt)
{
  wxExecute("python");
}
