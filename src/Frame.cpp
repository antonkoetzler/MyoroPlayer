#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_MENU(wxID_ABOUT, Frame::showAbout)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(1000, 800))
{
  wxIcon icon("../img/logo.png", wxBITMAP_TYPE_PNG);
  if (icon.IsOk()) SetIcon(icon);

  menubar = new MenuBar();
  interface = new Interface(this);

  SetSizer(interface);
  SetMenuBar(menubar);
  Centre();
}

Frame::~Frame() { this->Destroy(); }

void Frame::showAbout(wxCommandEvent& evt)
{
  aboutWindow = new About();
  aboutWindow->Show(true);
}

void Frame::exit(wxCommandEvent& evt) { Close(); }
