#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  // MenuBar events
  EVT_MENU(YT2MP3, Frame::yt2Mp3)
  EVT_MENU(CHANGE_DIR, Frame::changeDirectory)
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_MENU(SHOWCONTROLS, Frame::toggleControls)
  EVT_MENU(REFRESH, Frame::refreshPlaylist)
  EVT_MENU(QUEUE, Frame::queueSong)

  // Listbox events
  EVT_LISTBOX_DCLICK(SONGLIST, Frame::initSong)

  // Change directory events
  EVT_BUTTON(CHANGE_DIR_BUTTON, Frame::setDirectory)
  EVT_TEXT_ENTER(CHANGE_DIR_INP, Frame::setDirectory)
  EVT_BUTTON(YT2MP3_BUTTON, Frame::convertLink)
  EVT_TEXT_ENTER(YT2MP3_INP, Frame::convertLink)
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

  // Connect right click to bringing up popup menu
  playlist->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(Frame::playlistMenu), nullptr, this);

  SetMenuBar(menubar);
  SetSizer(sizer);
  Centre();
}

Frame::~Frame() { Destroy(); }

void Frame::exit(wxCommandEvent& evt) { Close(); }

void Frame::refreshPlaylist(wxCommandEvent& evt)
{
  sizer->Clear(false);

  wxString playlistDirectory = playlist->getPlaylistDirectory();
  delete playlist;
  playlist = new SongList(this, playlistDirectory);

  controls->setPlaylist(playlist);

  sizer->Add(playlist, 1, wxEXPAND);
  sizer->Add(controls, 0, wxEXPAND);
  sizer->Layout();
}

void Frame::toggleControls(wxCommandEvent& evt)
{
  if (!controls->IsShown()) controls->Show(true);
  else controls->Show(false);
  sizer->Layout();
}

void Frame::yt2Mp3(wxCommandEvent& evt)
{
  popup = new wxFrame(
    this,
    wxID_ANY,
    "Convert YouTube to MP3",
    wxDefaultPosition,
    wxSize(300, 87)
  );

  inp = new wxTextCtrl(
    popup,
    YT2MP3_INP,
    wxEmptyString,
    wxDefaultPosition,
    wxDefaultSize,
    wxTE_CENTRE | wxTE_PROCESS_ENTER
  );

  wxButton* button = new wxButton(
    popup,
    YT2MP3_BUTTON,
    "Convert",
    wxDefaultPosition,
    wxSize(300, 25),
    wxBORDER_NONE
  );

  wxBoxSizer* popupSizer = new wxBoxSizer(wxVERTICAL);
  popupSizer->Add(inp, 1, wxEXPAND);
  popupSizer->Add(button, 0, wxEXPAND);

  popup->SetSizer(popupSizer);
  popup->Show(true);
  popup->Centre();
}

void Frame::convertLink(wxCommandEvent& evt)
{
  if (inp->GetLineText(0) == wxEmptyString)
  {
    popup->Close(); popup->Destroy();
    delete popup; popup = nullptr;
    return;
  }

  #ifdef linux
    wxString command = "youtube-dl --extract-audio --audio-format mp3 -o \"" + playlist->getPlaylistDirectory() + "%(title)s-%(id)s.mp3\" " + inp->GetLineText(0);
  #endif
  #ifdef _WIN32
    wxString command = "youtube-dl.exe --extract-audio --audio-format mp3 -o \"" + playlist->getPlaylistDirectory() + "%(title)s-%(id)s.mp3\" " + inp->GetLineText(0);
  #endif
  wxExecute(command);

  wxMessageDialog* message = new wxMessageDialog(
    nullptr,
    "Refresh your playlist once the download has completed.",
    wxEmptyString,
    wxOK | wxCENTRE
  );
  message->ShowModal();

  popup->Close(); popup->Destroy();
  delete popup; popup = nullptr;
}

void Frame::changeDirectory(wxCommandEvent& evt)
{
  popup = new wxFrame(
    this,
    wxID_ANY,
    "Change Directory",
    wxDefaultPosition,
    wxSize(300, 87)
  );

  inp = new wxTextCtrl(
    popup,
    CHANGE_DIR_INP,
    wxEmptyString,
    wxDefaultPosition,
    wxDefaultSize,
    wxTE_CENTRE | wxTE_PROCESS_ENTER
  );

  wxButton* button = new wxButton(
    popup,
    CHANGE_DIR_BUTTON,
    "Set New Directory",
    wxDefaultPosition,
    wxSize(300, 25),
    wxBORDER_NONE
  );

  wxBoxSizer* popupSizer = new wxBoxSizer(wxVERTICAL);
  popupSizer->Add(inp, 1, wxEXPAND);
  popupSizer->Add(button, 0, wxEXPAND);

  popup->SetSizer(popupSizer);
  popup->Show(true);
  popup->Centre();
}

void Frame::setDirectory(wxCommandEvent& evt)
{
  if (inp->GetLineText(0) == wxEmptyString)
  {
    popup->Close(); popup->Destroy();
    delete popup; popup = nullptr;
    return;
  }

  sizer->Clear(false);

  delete playlist;
  playlist = new SongList(this, inp->GetLineText(0));

  controls->setPlaylist(playlist);

  sizer->Add(playlist, 1, wxEXPAND);
  sizer->Add(controls, 0, wxEXPAND);
  sizer->Layout();

  popup->Close(); popup->Destroy();
  delete popup; popup = nullptr;
}

void Frame::playlistMenu(wxMouseEvent& evt)
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

void Frame::queueSong(wxCommandEvent& evt)
{
  wxString song = playlist->GetString(playlist->GetSelection());
  wxString songDirectory = playlist->getPlaylistDirectory() + song;
  controls->addToQueue(songDirectory);
}

void Frame::initSong(wxCommandEvent& evt)
{
  // Making sure that controls are showing
  if (!controls->IsShown())
  {
    controls->Show(true);
    sizer->Layout();
  }

  wxString songDirectory = playlist->getPlaylistDirectory();
  songDirectory += evt.GetString();

  controls->initMediaPlayer(songDirectory);
}

