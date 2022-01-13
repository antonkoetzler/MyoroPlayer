#include "Frame.h"

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(1000, 800))
{
  menubar = new MenuBar();
  interface = new Interface(this);

  SetSizer(interface);
  SetMenuBar(menubar);
  Centre();
}
