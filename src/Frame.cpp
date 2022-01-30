#include "Frame.h"

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayer", wxDefaultPosition, wxSize(1400, 800))
{
  Center();
}

Frame::~Frame() { this->Destroy(); }

