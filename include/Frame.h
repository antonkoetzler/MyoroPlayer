#pragma once

#include <wx/wx.h>
#include "MenuBar.h"
#include "SongList.h"
#include "SideBar.h"
#include "Controls.h"

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  void quit(wxCommandEvent&);

 private:
  DECLARE_EVENT_TABLE();

  MenuBar* menubar;
  wxBoxSizer* sizer;
    SideBar* sidebar;
    wxBoxSizer* songSizer;
      SongList* songlist;
      Controls* controls;
};
