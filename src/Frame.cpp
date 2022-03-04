#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  // Menubar events
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_MENU(SHOWCONTROLS, Frame::showControls)
  EVT_MENU(YT2MP3, Frame::showYt2Mp3)
  EVT_MENU(SETDIR, Frame::showSetDirectory)
  EVT_MENU(REFRESH, Frame::refreshPlaylist)
  // Popup menu
  EVT_MENU(QUEUE, Frame::queueSong)

  // Playlist events
  EVT_LISTBOX_DCLICK(SONGLIST, Frame::setControls)

  // popupWindow events
  EVT_TEXT_ENTER(SETDIRINPUT, Frame::setDirectory)
  EVT_BUTTON(SETDIRBUTTON, Frame::setDirectory)
  EVT_TEXT_ENTER(YT2MP3INPUT, Frame::Yt2Mp3)
  EVT_BUTTON(YT2MP3BUTTON, Frame::Yt2Mp3)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(1000, 800))
{
  menubar = new MenuBar();
  SetMenuBar(menubar);

  playlist = new SongList(this);

  controls = new Controls(this);
  controls->setPlaylist(playlist);
  controls->Show(false);

  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(playlist, 1, wxEXPAND);
  sizer->Add(controls, 0, wxEXPAND);

  SetSizer(sizer);

  Centre();

  // Connect right click to bringing up popup menu
  playlist->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(Frame::playlistMenu), nullptr, this);
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
  if (!controls->IsShown())
  {
    controls->Show(true);
    sizer->Layout();
  }

  wxString songDirectory = playlistDirectory + evt.GetString();

  controls->addToSongCache(songDirectory);

  controls->setMediaPlayer(songDirectory);
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
    wxSize(250, 23),
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

  if (newDirectory == wxEmptyString) std::cout << "Empty" << std::endl;

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

    controls->setPlaylist(playlist);
    controls->setPlaylistDirectory(playlistDirectory);
  }

  delete dirTest; dirTest = nullptr;
}

void Frame::showYt2Mp3(wxCommandEvent& evt)
{
  popupWindow = new wxFrame(
    this,
    wxID_ANY,
    "Convert YouTube Link To MP3"
  );

  input = new wxTextCtrl(
    popupWindow,
    YT2MP3INPUT,
    wxEmptyString,
    wxDefaultPosition,
    wxSize(250, 23),
    wxTE_CENTRE | wxTE_PROCESS_ENTER
  );

  button = new wxButton(
    popupWindow,
    YT2MP3BUTTON,
    "Convert To MP3!",
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

void Frame::Yt2Mp3(wxCommandEvent& evt)
{
  // Making the youtube-dl command
  wxString command = "youtube-dl --extract-audio --audio-format mp3 -o \"" + playlistDirectory + "%(title)s-%(id)s.mp3\" " + input->GetLineText(0);
  wxExecute(command);

  wxMessageDialog* message = new wxMessageDialog(
    nullptr,
    "Make sure to refresh your playlist directory\nafter the download has completed",
    wxEmptyString,
    wxOK | wxCENTRE
  );
  message->ShowModal();

  popupWindow->Close();
  delete popupWindow; popupWindow = nullptr;
}

void Frame::playlistMenu(wxMouseEvent& evt)
{
  wxClientDC dc(this);
  playlist->SetSelection(playlist->HitTest(evt.GetLogicalPosition(dc)));

  wxMenuItem* popupQueue = new wxMenuItem(
    nullptr,
    QUEUE,
    "Queue Song"
  );

  wxMenu* popup = new wxMenu();
  popup->Append(popupQueue);

  PopupMenu(popup, wxDefaultPosition);
}

void Frame::queueSong(wxCommandEvent& evt)
{
  wxString song = playlist->GetString(playlist->GetSelection());
  wxString songDirectory = playlistDirectory + song;
  controls->addToQueue(songDirectory);
}

void Frame::refreshPlaylist(wxCommandEvent& evt)
{
  bool showControls = controls->IsShown();

  sizer->Clear(false);

  delete playlist; playlist = nullptr;
  playlist = new SongList(this, playlistDirectory);

  sizer->Add(playlist, 1, wxEXPAND);
  sizer->Add(controls, 0, wxEXPAND);

  sizer->Layout();
}
