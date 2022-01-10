#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_MENU(wxID_ABOUT, Frame::showAbout)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(800, 500))
{
  menubar = new MenuBar();

  SetMenuBar(menubar);
  Center();
}

void Frame::exit(wxCommandEvent& evt) { Close(); }

void Frame::showAbout(wxCommandEvent& evt)
{
  std::cout << "Working" << std::endl;
}
