// Lists playlists on the side
#pragma once

#include <wx/wx.h>

class SideBar : public wxPanel
{
 public:
  SideBar(wxFrame*);

 private:
  wxBoxSizer* sizer;
  wxButton* test1;
  wxButton* test2;
};
