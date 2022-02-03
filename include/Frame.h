#pragma once

#include <wx/wx.h>
#include "SongList.h"
#include "MenuBar.h"

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

 private:
  // Sizer for dividing song list, music controls, etc
  wxBoxSizer* ui;
  SongList* songlist;
  MenuBar* menubar;
};

