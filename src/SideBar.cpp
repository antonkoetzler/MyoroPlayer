#include "SideBar.h"

SideBar::SideBar(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(100, 600))
{
  SetBackgroundColour(wxColour(170, 74, 68));

  test1 = new wxButton(
    this,
    wxID_ANY,
    "Playlist",
    wxDefaultPosition,
    wxSize(100, 50),
    wxBORDER_NONE
  );
  test2 = new wxButton(
    this,
    wxID_ANY,
    "Playlist",
    wxDefaultPosition,
    wxSize(100, 50),
    wxBORDER_NONE
  );

  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(test1, 0);
  sizer->Add(test2, 0);
  SetSizer(sizer);
}
