#pragma once

#include <wx/wx.h>
#include "SongList.h"
#include "MenuBar.h"
#include "Controls.h"

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

 private:
  wxBoxSizer* ui; // Sizer for dividing song list, music controls, etc
  SongList* songlist;
  MenuBar* menubar;
  Controls* controls;
};

